var github = (function(){
  function render(target, repos){
    var i = 0, fragment = '', t = $(target)[0];

    for(i = 0; i < repos.length; i++) {
      fragment += '<li><a href="'+repos[i].url+'">'+repos[i].name+'</a><p>'+repos[i].description+'</p></li>';
    }
    t.innerHTML = fragment;
  }
  return {
    showRepos: function(options){
      $.ajax({
          url: "http://github.com/api/v2/json/repos/show/"+options.user+"?callback=?"
        , type: 'jsonp'
        , error: function (err) { $(options.target + ' li.loading').addClass('error').text("Error loading feed"); }
        , success: function(data) {
          var repos = [];
          for (var i = 0; i < data.repositories.length; i++){
            if (options.skip_forks && data.repositories[i].fork) { continue; }
            repos.push(data.repositories[i]);
          }
          repos.sort(function(a, b) {
            var aDate = new Date(a.pushed_at).valueOf(),
                bDate = new Date(b.pushed_at).valueOf();

            if (aDate === bDate) { return 0; }
            return aDate > bDate ? -1 : 1;
          });

          if (options.count) { repos.splice(options.count); }
          render(options.target, repos);
        }
      })
    }
  };
})();

// ## Client-side Javascript API wrapper for GitHub
//
// Tries to map one-to-one with the GitHub API V2, but in a Javascripty manner.

(function (globals) {

    // Before we implement the API methods, we will define all of our private
    // variables and helper functions with one `var` statement.
    var

    // The username and authentication token of the library's user.
    authUsername,
    authToken,

    // To save keystrokes when we make JSONP calls to the HTTP API, we will keep
    // track of the root from which all V2 urls extend.
    apiRoot = "https://github.com/api/v2/json/",

    // Send a JSONP request to the Github API that calls `callback` with
    // the `context` argument as `this`.
    //
    // The `url` parameter is concatenated with the apiRoot, for the reasons
    // mentioned above. The way that we are supporting non-global, anonymous
    // functions is by sticking them in the globally exposed
    // `gh.__jsonp_callbacks` object with a "unique" `id` that is the current
    // time in milliseconds. Once the callback is called, it is deleted from the
    // object to prevent memory leaks.
    jsonp = function (url, callback, context) {
        var id = +new Date,
        script = document.createElement("script");

        while (gh.__jsonp_callbacks[id] !== undefined)
            id += Math.random(); // Avoid slight possibility of id clashes.

        gh.__jsonp_callbacks[id] = function () {
            delete gh.__jsonp_callbacks[id];
            callback.apply(context, arguments);
        };

        var prefix = "?";
        if (url.indexOf("?") >= 0)
            prefix = "&";

        url += prefix + "callback=" + encodeURIComponent("gh.__jsonp_callbacks[" + id + "]");
        if (authUsername && authToken) {
            url += "&login=" + authUsername + "&authToken=" + authToken;
        }
        script.setAttribute("src", apiRoot + url);

        document.getElementsByTagName('head')[0].appendChild(script);
    },

    // Send an HTTP POST. Unfortunately, it isn't possible to support a callback
    // with the resulting data. (Please prove me wrong if you can!)
    //
    // This is implemented with a hack to get around the cross-domain
    // restrictions on ajax calls. Basically, a form is created that will POST
    // to the GitHub API URL, stuck inside an iframe so that it won't redirect
    // this page, and then submitted.
    post = function (url, vals) {
        var
        form = document.createElement("form"),
        iframe = document.createElement("iframe"),
        doc = iframe.contentDocument !== undefined ?
            iframe.contentDocument :
            iframe.contentWindow.document,
        key, field;
        vals = vals || {};

        form.setAttribute("method", "post");
        form.setAttribute("action", apiRoot + url);
        for (key in vals) {
            if (vals.hasOwnProperty(key)) {
                field = document.createElement("input");
                field.type = "hidden";
                field.value = encodeURIComponent(vals[key]);
                form.appendChild(field);
            }
        }

        iframe.setAttribute("style", "display: none;");
        doc.body.appendChild(form);
        document.body.appendChild(iframe);
        form.submit();
    },

    // This helper function will throw a TypeError if the library user is not
    // properly authenticated. Otherwise, it silently returns.
    authRequired = function (username) {
        if (!authUsername || !authToken || authUsername !== username) {
            throw new TypeError("gh: Must be authenticated to do that.");
        }
    },

    // Convert an object to a url parameter string.
    //
    //     paramify({foo:1, bar:3}) -> "foo=1&bar=3".
    paramify = function (params) {
        var str = "", key;
        for (key in params) if (params.hasOwnProperty(key))
            str += key + "=" + params[key] + "&";
        return str.replace(/&$/, "");
    },

    // Get around how the GH team haven't migrated all the API to version 2, and
    // how gists use a different api root.
    withTempApiRoot = function (tempApiRoot, fn) {
        return function () {
            var oldRoot = apiRoot;
            apiRoot = tempApiRoot;
            fn.apply(this, arguments);
            apiRoot = oldRoot;
        };
    },

    // Expose the global `gh` variable, through which every API method is
    // accessed, but keep a local variable around so we can reference it easily.
    gh = globals.gh = {};

    // Psuedo private home for JSONP callbacks (which are required to be global
    // by the nature of JSONP, as discussed earlier).
    gh.__jsonp_callbacks = {};

    // Authenticate as a user. Does not try to validate at any point; that job
    // is up to each individual method, which calls `authRequired` as needed.
    gh.authenticate = function (username, token) {
        authUsername = username;
        authToken = token;
        return this;
    };

    // ### Users

    // The constructor for user objects. Just creating an instance of a user
    // doesn't fetch any data from GitHub, you need to get explicit about what
    // you want to do that.
    //
    //     var huddlej = gh.user("huddlej");
    gh.user = function (username) {
        if ( !(this instanceof gh.user)) {
            return new gh.user(username);
        }
        this.username = username;
    };

    // Show basic user info; you can get more info if you are authenticated as
    // this user.
    //
    //    gh.user("fitzgen").show(function (data) {
    //        console.log(data.user);
    //    });
    gh.user.prototype.show = function (callback, context) {
        jsonp("user/show/" + this.username, callback, context);
        return this;
    };

    // Update a user's info. You must be authenticated as this user for this to
    // succeed.
    //
    //     TODO: example
    gh.user.prototype.update = function (params) {
        authRequired(this.username);
        var key, postData = {
            login: authUsername,
            token: authToken
        };
        for (key in params) {
            if (params.hasOwnProperty(key)) {
                postData["values["+key+"]"] = encodeURIComponent(params[key]);
            }
        }
        post("user/show/" + this.username, postData);
        return this;
    };

    // Get a list of who this user is following.
    //
    //     TODO: example
    gh.user.prototype.following = function (callback, context) {
        jsonp("user/show/" + this.username + "/following", callback, context);
    };

    // Find out what other users are following this user.
    //
    //     TODO: example
    gh.user.prototype.followers = function (callback, context) {
        jsonp("user/show/" + this.username + "/followers", callback, context);
    };

    // Make this user follow some other user. You must be authenticated as this
    // user for this to succeed.
    //
    //     TODO: example
    gh.user.prototype.follow = function (user) {
        authRequired.call(this);
        post("user/follow/" + user);
        return this;
    };

    // Make this user quit following the given `user`. You must be authenticated
    // as this user to succeed.
    //
    //     TODO: example
    gh.user.prototype.unfollow = function (user) {
        authRequired.call(this);
        post("user/unfollow/" + user);
        return this;
    };

    // Get a list of repositories that this user is watching.
    //
    //     TODO: example
    gh.user.prototype.watching = function (callback, context) {
        jsonp("repos/watched/" + this.username, callback, context);
        return this;
    };

    // Get a list of this user's repositories.
    //
    //     gh.user("fitzgen").repos(function (data) {
    //         alert(data.repositories.length);
    //     });
    gh.user.prototype.repos = function (callback, context) {
        gh.repo.forUser(this.username, callback, context);
        return this;
    };

    // Make this user fork the repo that lives at
    // http://github.com/user/repo. You must be authenticated as this user for
    // this to succeed.
    //
    //     gh.user("fitzgen").forkRepo("brianleroux", "wtfjs");
    gh.user.prototype.forkRepo = function (user, repo) {
        authRequired(this.username);
        post("repos/fork/" + user + "/" + repo);
        return this;
    };

    // Get a list of all repos that this user can push to (including ones that
    // they are just a collaborator on, and do not own). Must be authenticated
    // as this user.
    gh.user.prototype.pushable = function (callback, context) {
        authRequired(authUsername);
        jsonp("repos/pushable", callback, context);
    };

    gh.user.prototype.publicGists = withTempApiRoot(
        "http://gist.github.com/api/v1/json/gists/",
        function (callback, context) {
            jsonp(this.username, callback, context);
            return this;
        }
    );

    // Search users for `query`.
    gh.user.search = function (query, callback, context) {
        jsonp("user/search/" + query, callback, context);
        return this;
    };

    // ### Repositories

    // This is the base constructor for creating repo objects. Note that this
    // won't actually hit the GitHub API until you specify what data you want,
    // or what action you wish to take via a prototype method.
    gh.repo = function (user, repo) {
        if ( !(this instanceof gh.repo)) {
            return new gh.repo(user, repo);
        }
        this.repo = repo;
        this.user = user;
    };

    // Get basic information on this repo.
    //
    //     gh.repo("schacon", "grit").show(function (data) {
    //         console.log(data.repository.description);
    //     });
    gh.repo.prototype.show = function (callback, context) {
        jsonp("repos/show/" + this.user + "/" + this.repo, callback, context);
        return this;
    };

    // Update the information for this repo. Must be authenticated as the
    // repository owner. Params can include:
    //
    //   * description
    //   * homepage
    //   * has_wiki
    //   * has_issues
    //   * has_downloads
    gh.repo.prototype.update = function (params) {
        authRequired(this.user);
        var key, postData = {
            login: authUsername,
            token: authToken
        };
        for (key in params) {
            if (params.hasOwnProperty(key)) {
                postData["values["+key+"]"] = encodeURIComponent(params[key]);
            }
        }
        post("repos/show/" + this.user + "/" + this.repo, postData);
        return this;
    };

    // Get all tags for this repo.
    gh.repo.prototype.tags = function (callback, context) {
        jsonp("repos/show/" + this.user + "/" + this.repo + "/tags",
              callback,
              context);
        return this;
    };

    // Get all branches in this repo.
    gh.repo.prototype.branches = function (callback, context) {
        jsonp("repos/show/" + this.user + "/" + this.repo + "/branches",
              callback,
              context);
        return this;
    };

    // Gather line count information on the language(s) used in this repo.
    gh.repo.prototype.languages = function (callback, context) {
        jsonp("/repos/show/" + this.user + "/" + this.repo + "/languages",
              callback,
              context);
        return this;
    };

    // Gather data on all the forks of this repo.
    gh.repo.prototype.network = function (callback, context) {
        jsonp("repos/show/" + this.user + "/" + this.repo + "/network",
              callback,
              context);
        return this;
    };

    // All users who have contributed to this repo. Pass `true` to showAnon if you
    // want to see the non-github contributors.
    gh.repo.prototype.contributors = function (callback, context, showAnon) {
        var url = "repos/show/" + this.user + "/" + this.repo + "/contributors";
        if (showAnon)
            url += "/anon";
        jsonp(url,
              callback,
              context);
        return this;
    };

    // Get all of the collaborators for this repo.
    gh.repo.prototype.collaborators = function (callback, context) {
        jsonp("repos/show/" + this.user + "/" + this.repo + "/collaborators",
              callback,
              context);
        return this;
    };

    // Add a collaborator to this project. Must be authenticated.
    gh.repo.prototype.addCollaborator = function (collaborator) {
        authRequired(this.user);
        post("repos/collaborators/" + this.repo + "/add/" + collaborator);
        return this;
    };

    // Remove a collaborator from this project. Must be authenticated.
    gh.repo.prototype.removeCollaborator = function (collaborator) {
        authRequired(this.user);
        post("repos/collaborators/" + this.repo + "/remove/" + collaborator);
        return this;
    };

    // Make this repository private. Authentication required.
    gh.repo.prototype.setPrivate = function () {
        authRequired(this.user);
        post("repo/set/private/" + this.repo);
        return this;
    };

    // Make this repository public. Authentication required.
    gh.repo.prototype.setPublic = function () {
        authRequired(this.user);
        post("repo/set/public/" + this.repo);
        return this;
    };

    // Search for repositories. `opts` may include `start_page` or `language`,
    // which must be capitalized.
    gh.repo.search = function (query, opts, callback, context) {
        var url = "repos/search/" + query.replace(" ", "+");
        if (typeof opts === "function") {
            opts = {};
            callback = arguments[1];
            context = arguments[2];
        }
        url += "?" + paramify(opts);
        return this;
    };

    // Get all the repos that are owned by `user`.
    gh.repo.forUser = function (user, callback, context) {
        jsonp("repos/show/" + user, callback, context);
        return this;
    };

    // Create a repository. Must be authenticated.
    gh.repo.create = function (name, opts) {
        authRequired(authUsername);
        opts.name = name;
        post("repos/create", opts);
        return this;
    };

    // Delete a repository. Must be authenticated.
    gh.repo.del = function (name) {
        authRequired(authUsername);
        post("repos/delete/" + name);
        return this;
    };

    // ### Commits

    gh.commit = function (user, repo, sha) {
        if ( !(this instanceof gh.commit) )
            return new gh.commit(user, repo, sha);
        this.user = user;
        this.repo = repo;
        this.sha = sha;
    };

    gh.commit.prototype.show = function (callback, context) {
        jsonp("commits/show/" + this.user + "/" + this.repo + "/" + this.sha,
              callback,
              context);
        return this;
    };

    // Get a list of all commits on a repos branch.
    gh.commit.forBranch = function (user, repo, branch, callback, context) {
        jsonp("commits/list/" + user + "/" + repo + "/" + branch,
              callback,
              context);
        return this;
    };

    // Get a list of all commits on this path (file or dir).
    gh.commit.forPath = function (user, repo, branch, path, callback, context) {
        jsonp("commits/list/" + user + "/" + repo + "/" + branch + "/" + path,
              callback,
              context);
        return this;
    };

    // ### Issues

    gh.issue = function (user, repo, number) {
        if ( !(this instanceof gh.issue) )
            return new gh.commit(user, repo, number);
        this.user = user;
        this.repo = repo;
        this.number = number;
    };

    // View this issue's info.
    gh.issue.prototype.show = function (callback, context) {
        jsonp("issues/show/" + this.user + "/" + this.repo + "/" + this.number,
              callback,
              context);
        return this;
    };

    // Get a list of all comments on this issue.
    gh.issue.prototype.comments = function (callback, context) {
        jsonp("issues/comments/" + this.user + "/" + this.repo + "/" + this.number,
              callback,
              context);
        return this;
    };

    // Close this issue.
    gh.issue.prototype.close = function () {
        authRequired(this.user);
        post("issues/close/" + this.user + "/" + this.repo + "/" + this.number);
        return this;
    };

    // Reopen this issue.
    gh.issue.prototype.reopen = function () {
        authRequired(this.user);
        post("issues/reopen/" + this.user + "/" + this.repo + "/" + this.number);
        return this;
    };

    // Reopen this issue.
    gh.issue.prototype.update = function (title, body) {
        authRequired(this.user);
        post("issues/edit/" + this.user + "/" + this.repo + "/" + this.number, {
            title: title,
            body: body
        });
        return this;
    };

    // Add `label` to this issue. If the label is not yet in the system, it will
    // be created.
    gh.issue.prototype.addLabel = function (label) {
        post("issues/label/add/" + this.user + "/" + this.repo + "/" + label + "/" + this.number);
        return this;
    };

    // Remove a label from this issue.
    gh.issue.prototype.removeLabel = function (label) {
        post("issues/label/remove/" + this.user + "/" + this.repo + "/" + label + "/" + this.number);
        return this;
    };

    // Comment on this issue as the user that is authenticated.
    gh.issue.prototype.comment = function (comment) {
        authRequired(authUsername);
        post("/issues/comment/" + user + "/" + repo + "/" + this.number, {
            comment: comment
        });
        return this;
    };

    // Get all issues' labels for the repo.
    gh.issue.labels = function (user, repo) {
        jsonp("issues/labels/" + user + "/" + repo,
              callback,
              context);
        return this;
    };

    // Open an issue. Must be authenticated.
    gh.issue.open = function (repo, title, body) {
        authRequired(authUsername);
        post("issues/open/" + authUsername + "/" + repo, {
            title: title,
            body: body
        });
        return this;
    };

    // Search a repository's issue tracker. `state` can be "open" or "closed".
    gh.issue.search = function (user, repo, state, query, callback, context) {
        jsonp("/issues/search/" + user + "/" + repo + "/" + state + "/" + query,
              callback,
              context);
        return this;
    };

    // Get a list of issues for the given repo. `state` can be "open" or
    // "closed".
    gh.issue.list = function (user, repo, state, callback, context) {
        jsonp("issues/list/" + user + "/" + repo + "/" + state,
              callback,
              context);
        return this;
    };

    // ### Gists

    gh.gist = function (id) {
        if ( !(this instanceof gh.gist) ) {
            return new gh.gist(id);
        }
        this.id = id;
    };

    gh.gist.prototype.show = withTempApiRoot(
        "http://gist.github.com/api/v1/json/",
        function (callback, context) {
            jsonp(this.id, callback, cont);
            return this;
        }
    );

    gh.gist.prototype.file = withTempApiRoot(
        "http://gist.github.com/raw/v1/json/",
        function (filename, callback, context) {
            jsonp(this.id + "/" + filename, callback, cont);
            return this;
        }
    );

    // ### Objects

    gh.object = function (user, repo) {
        if (!(this instanceof gh.object)) {
            return new gh.object(user, repo);
        }
        this.user = user;
        this.repo = repo;
    };

    // Get the contents of a tree by tree SHA
    gh.object.prototype.tree = function (sha, callback, context) {
        jsonp("tree/show/" + this.user + "/" + this.repo + "/" + sha,
              callback,
              context);
        return this;
    };

    // Get the data about a blob by tree SHA and path
    gh.object.prototype.blob = function (path, sha, callback, context) {
        jsonp("blob/show/" + this.user + "/" + this.repo + "/" + sha + "/" + path,
              callback,
              context);
        return this;
    };

    // Get only blob meta
    gh.object.prototype.blobMeta = function (path, sha, callback, context) {
        jsonp("blob/show/" + this.user + "/" + this.repo + "/" + sha + "/" + path + "?meta=1",
              callback,
              context);
        return this;
    };

    // Get list of blobs
    gh.object.prototype.blobAll = function (branch, callback, context) {
        jsonp("blob/all/" + this.user + "/" + this.repo + "/" + branch,
              callback,
              context);
        return this;
    };

    // Get meta of each blob in tree
    gh.object.prototype.blobFull = function (sha, callback, context) {
        jsonp("blob/full/" + this.user + "/" + this.repo + "/" + sha,
              callback,
              context);
        return this;
    };

    // ### Network

    gh.network = function(user, repo) {
        if (!(this instanceof gh.network)) {
            return new gh.network(user, repo);
        }
        this.user = user;
        this.repo = repo;
    };

    gh.network.prototype.data = withTempApiRoot(
        "http://github.com/",
        function (nethash, start, end, callback, context) {
            jsonp(this.user + "/" + this.repo + "/network_data_chunk?"
                  + nethash + "&" + start + "&" + end,
                  callback,
                  context);
            return this;
        }
    );

    gh.network.prototype.meta = withTempApiRoot(
        "http://github.com/",
        function (callback, context) {
            jsonp(this.user + "/" + this.repo + "/network_meta",
                  callback,
                  context);
            return this;
        }
    );

}(window));

/*
 * A JavaScript implementation of the RSA Data Security, Inc. MD5 Message
 * Digest Algorithm, as defined in RFC 1321.
 * Version 2.2 Copyright (C) Paul Johnston 1999 - 2009
 * Other contributors: Greg Holt, Andrew Kepert, Ydnar, Lostinet
 * Distributed under the BSD License
 * See http://pajhome.org.uk/crypt/md5 for more info.
 */

/*
 * Configurable variables. You may need to tweak these to be compatible with
 * the server-side, but the defaults work in most cases.
 */
var hexcase = 0;   /* hex output format. 0 - lowercase; 1 - uppercase        */
var b64pad  = "";  /* base-64 pad character. "=" for strict RFC compliance   */

/*
 * These are the functions you'll usually want to call
 * They take string arguments and return either hex or base-64 encoded strings
 */
function hex_md5(s)    { return rstr2hex(rstr_md5(str2rstr_utf8(s))); }
function b64_md5(s)    { return rstr2b64(rstr_md5(str2rstr_utf8(s))); }
function any_md5(s, e) { return rstr2any(rstr_md5(str2rstr_utf8(s)), e); }
function hex_hmac_md5(k, d)
  { return rstr2hex(rstr_hmac_md5(str2rstr_utf8(k), str2rstr_utf8(d))); }
function b64_hmac_md5(k, d)
  { return rstr2b64(rstr_hmac_md5(str2rstr_utf8(k), str2rstr_utf8(d))); }
function any_hmac_md5(k, d, e)
  { return rstr2any(rstr_hmac_md5(str2rstr_utf8(k), str2rstr_utf8(d)), e); }

/*
 * Perform a simple self-test to see if the VM is working
 */
function md5_vm_test()
{
  return hex_md5("abc").toLowerCase() == "900150983cd24fb0d6963f7d28e17f72";
}

/*
 * Calculate the MD5 of a raw string
 */
function rstr_md5(s)
{
  return binl2rstr(binl_md5(rstr2binl(s), s.length * 8));
}

/*
 * Calculate the HMAC-MD5, of a key and some data (raw strings)
 */
function rstr_hmac_md5(key, data)
{
  var bkey = rstr2binl(key);
  if(bkey.length > 16) bkey = binl_md5(bkey, key.length * 8);

  var ipad = Array(16), opad = Array(16);
  for(var i = 0; i < 16; i++)
  {
    ipad[i] = bkey[i] ^ 0x36363636;
    opad[i] = bkey[i] ^ 0x5C5C5C5C;
  }

  var hash = binl_md5(ipad.concat(rstr2binl(data)), 512 + data.length * 8);
  return binl2rstr(binl_md5(opad.concat(hash), 512 + 128));
}

/*
 * Convert a raw string to a hex string
 */
function rstr2hex(input)
{
  try { hexcase } catch(e) { hexcase=0; }
  var hex_tab = hexcase ? "0123456789ABCDEF" : "0123456789abcdef";
  var output = "";
  var x;
  for(var i = 0; i < input.length; i++)
  {
    x = input.charCodeAt(i);
    output += hex_tab.charAt((x >>> 4) & 0x0F)
           +  hex_tab.charAt( x        & 0x0F);
  }
  return output;
}

/*
 * Convert a raw string to a base-64 string
 */
function rstr2b64(input)
{
  try { b64pad } catch(e) { b64pad=''; }
  var tab = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  var output = "";
  var len = input.length;
  for(var i = 0; i < len; i += 3)
  {
    var triplet = (input.charCodeAt(i) << 16)
                | (i + 1 < len ? input.charCodeAt(i+1) << 8 : 0)
                | (i + 2 < len ? input.charCodeAt(i+2)      : 0);
    for(var j = 0; j < 4; j++)
    {
      if(i * 8 + j * 6 > input.length * 8) output += b64pad;
      else output += tab.charAt((triplet >>> 6*(3-j)) & 0x3F);
    }
  }
  return output;
}

/*
 * Convert a raw string to an arbitrary string encoding
 */
function rstr2any(input, encoding)
{
  var divisor = encoding.length;
  var i, j, q, x, quotient;

  /* Convert to an array of 16-bit big-endian values, forming the dividend */
  var dividend = Array(Math.ceil(input.length / 2));
  for(i = 0; i < dividend.length; i++)
  {
    dividend[i] = (input.charCodeAt(i * 2) << 8) | input.charCodeAt(i * 2 + 1);
  }

  /*
   * Repeatedly perform a long division. The binary array forms the dividend,
   * the length of the encoding is the divisor. Once computed, the quotient
   * forms the dividend for the next step. All remainders are stored for later
   * use.
   */
  var full_length = Math.ceil(input.length * 8 /
                                    (Math.log(encoding.length) / Math.log(2)));
  var remainders = Array(full_length);
  for(j = 0; j < full_length; j++)
  {
    quotient = Array();
    x = 0;
    for(i = 0; i < dividend.length; i++)
    {
      x = (x << 16) + dividend[i];
      q = Math.floor(x / divisor);
      x -= q * divisor;
      if(quotient.length > 0 || q > 0)
        quotient[quotient.length] = q;
    }
    remainders[j] = x;
    dividend = quotient;
  }

  /* Convert the remainders to the output string */
  var output = "";
  for(i = remainders.length - 1; i >= 0; i--)
    output += encoding.charAt(remainders[i]);

  return output;
}

/*
 * Encode a string as utf-8.
 * For efficiency, this assumes the input is valid utf-16.
 */
function str2rstr_utf8(input)
{
  var output = "";
  var i = -1;
  var x, y;

  while(++i < input.length)
  {
    /* Decode utf-16 surrogate pairs */
    x = input.charCodeAt(i);
    y = i + 1 < input.length ? input.charCodeAt(i + 1) : 0;
    if(0xD800 <= x && x <= 0xDBFF && 0xDC00 <= y && y <= 0xDFFF)
    {
      x = 0x10000 + ((x & 0x03FF) << 10) + (y & 0x03FF);
      i++;
    }

    /* Encode output as utf-8 */
    if(x <= 0x7F)
      output += String.fromCharCode(x);
    else if(x <= 0x7FF)
      output += String.fromCharCode(0xC0 | ((x >>> 6 ) & 0x1F),
                                    0x80 | ( x         & 0x3F));
    else if(x <= 0xFFFF)
      output += String.fromCharCode(0xE0 | ((x >>> 12) & 0x0F),
                                    0x80 | ((x >>> 6 ) & 0x3F),
                                    0x80 | ( x         & 0x3F));
    else if(x <= 0x1FFFFF)
      output += String.fromCharCode(0xF0 | ((x >>> 18) & 0x07),
                                    0x80 | ((x >>> 12) & 0x3F),
                                    0x80 | ((x >>> 6 ) & 0x3F),
                                    0x80 | ( x         & 0x3F));
  }
  return output;
}

/*
 * Encode a string as utf-16
 */
function str2rstr_utf16le(input)
{
  var output = "";
  for(var i = 0; i < input.length; i++)
    output += String.fromCharCode( input.charCodeAt(i)        & 0xFF,
                                  (input.charCodeAt(i) >>> 8) & 0xFF);
  return output;
}

function str2rstr_utf16be(input)
{
  var output = "";
  for(var i = 0; i < input.length; i++)
    output += String.fromCharCode((input.charCodeAt(i) >>> 8) & 0xFF,
                                   input.charCodeAt(i)        & 0xFF);
  return output;
}

/*
 * Convert a raw string to an array of little-endian words
 * Characters >255 have their high-byte silently ignored.
 */
function rstr2binl(input)
{
  var output = Array(input.length >> 2);
  for(var i = 0; i < output.length; i++)
    output[i] = 0;
  for(var i = 0; i < input.length * 8; i += 8)
    output[i>>5] |= (input.charCodeAt(i / 8) & 0xFF) << (i%32);
  return output;
}

/*
 * Convert an array of little-endian words to a string
 */
function binl2rstr(input)
{
  var output = "";
  for(var i = 0; i < input.length * 32; i += 8)
    output += String.fromCharCode((input[i>>5] >>> (i % 32)) & 0xFF);
  return output;
}

/*
 * Calculate the MD5 of an array of little-endian words, and a bit length.
 */
function binl_md5(x, len)
{
  /* append padding */
  x[len >> 5] |= 0x80 << ((len) % 32);
  x[(((len + 64) >>> 9) << 4) + 14] = len;

  var a =  1732584193;
  var b = -271733879;
  var c = -1732584194;
  var d =  271733878;

  for(var i = 0; i < x.length; i += 16)
  {
    var olda = a;
    var oldb = b;
    var oldc = c;
    var oldd = d;

    a = md5_ff(a, b, c, d, x[i+ 0], 7 , -680876936);
    d = md5_ff(d, a, b, c, x[i+ 1], 12, -389564586);
    c = md5_ff(c, d, a, b, x[i+ 2], 17,  606105819);
    b = md5_ff(b, c, d, a, x[i+ 3], 22, -1044525330);
    a = md5_ff(a, b, c, d, x[i+ 4], 7 , -176418897);
    d = md5_ff(d, a, b, c, x[i+ 5], 12,  1200080426);
    c = md5_ff(c, d, a, b, x[i+ 6], 17, -1473231341);
    b = md5_ff(b, c, d, a, x[i+ 7], 22, -45705983);
    a = md5_ff(a, b, c, d, x[i+ 8], 7 ,  1770035416);
    d = md5_ff(d, a, b, c, x[i+ 9], 12, -1958414417);
    c = md5_ff(c, d, a, b, x[i+10], 17, -42063);
    b = md5_ff(b, c, d, a, x[i+11], 22, -1990404162);
    a = md5_ff(a, b, c, d, x[i+12], 7 ,  1804603682);
    d = md5_ff(d, a, b, c, x[i+13], 12, -40341101);
    c = md5_ff(c, d, a, b, x[i+14], 17, -1502002290);
    b = md5_ff(b, c, d, a, x[i+15], 22,  1236535329);

    a = md5_gg(a, b, c, d, x[i+ 1], 5 , -165796510);
    d = md5_gg(d, a, b, c, x[i+ 6], 9 , -1069501632);
    c = md5_gg(c, d, a, b, x[i+11], 14,  643717713);
    b = md5_gg(b, c, d, a, x[i+ 0], 20, -373897302);
    a = md5_gg(a, b, c, d, x[i+ 5], 5 , -701558691);
    d = md5_gg(d, a, b, c, x[i+10], 9 ,  38016083);
    c = md5_gg(c, d, a, b, x[i+15], 14, -660478335);
    b = md5_gg(b, c, d, a, x[i+ 4], 20, -405537848);
    a = md5_gg(a, b, c, d, x[i+ 9], 5 ,  568446438);
    d = md5_gg(d, a, b, c, x[i+14], 9 , -1019803690);
    c = md5_gg(c, d, a, b, x[i+ 3], 14, -187363961);
    b = md5_gg(b, c, d, a, x[i+ 8], 20,  1163531501);
    a = md5_gg(a, b, c, d, x[i+13], 5 , -1444681467);
    d = md5_gg(d, a, b, c, x[i+ 2], 9 , -51403784);
    c = md5_gg(c, d, a, b, x[i+ 7], 14,  1735328473);
    b = md5_gg(b, c, d, a, x[i+12], 20, -1926607734);

    a = md5_hh(a, b, c, d, x[i+ 5], 4 , -378558);
    d = md5_hh(d, a, b, c, x[i+ 8], 11, -2022574463);
    c = md5_hh(c, d, a, b, x[i+11], 16,  1839030562);
    b = md5_hh(b, c, d, a, x[i+14], 23, -35309556);
    a = md5_hh(a, b, c, d, x[i+ 1], 4 , -1530992060);
    d = md5_hh(d, a, b, c, x[i+ 4], 11,  1272893353);
    c = md5_hh(c, d, a, b, x[i+ 7], 16, -155497632);
    b = md5_hh(b, c, d, a, x[i+10], 23, -1094730640);
    a = md5_hh(a, b, c, d, x[i+13], 4 ,  681279174);
    d = md5_hh(d, a, b, c, x[i+ 0], 11, -358537222);
    c = md5_hh(c, d, a, b, x[i+ 3], 16, -722521979);
    b = md5_hh(b, c, d, a, x[i+ 6], 23,  76029189);
    a = md5_hh(a, b, c, d, x[i+ 9], 4 , -640364487);
    d = md5_hh(d, a, b, c, x[i+12], 11, -421815835);
    c = md5_hh(c, d, a, b, x[i+15], 16,  530742520);
    b = md5_hh(b, c, d, a, x[i+ 2], 23, -995338651);

    a = md5_ii(a, b, c, d, x[i+ 0], 6 , -198630844);
    d = md5_ii(d, a, b, c, x[i+ 7], 10,  1126891415);
    c = md5_ii(c, d, a, b, x[i+14], 15, -1416354905);
    b = md5_ii(b, c, d, a, x[i+ 5], 21, -57434055);
    a = md5_ii(a, b, c, d, x[i+12], 6 ,  1700485571);
    d = md5_ii(d, a, b, c, x[i+ 3], 10, -1894986606);
    c = md5_ii(c, d, a, b, x[i+10], 15, -1051523);
    b = md5_ii(b, c, d, a, x[i+ 1], 21, -2054922799);
    a = md5_ii(a, b, c, d, x[i+ 8], 6 ,  1873313359);
    d = md5_ii(d, a, b, c, x[i+15], 10, -30611744);
    c = md5_ii(c, d, a, b, x[i+ 6], 15, -1560198380);
    b = md5_ii(b, c, d, a, x[i+13], 21,  1309151649);
    a = md5_ii(a, b, c, d, x[i+ 4], 6 , -145523070);
    d = md5_ii(d, a, b, c, x[i+11], 10, -1120210379);
    c = md5_ii(c, d, a, b, x[i+ 2], 15,  718787259);
    b = md5_ii(b, c, d, a, x[i+ 9], 21, -343485551);

    a = safe_add(a, olda);
    b = safe_add(b, oldb);
    c = safe_add(c, oldc);
    d = safe_add(d, oldd);
  }
  return Array(a, b, c, d);
}

/*
 * These functions implement the four basic operations the algorithm uses.
 */
function md5_cmn(q, a, b, x, s, t)
{
  return safe_add(bit_rol(safe_add(safe_add(a, q), safe_add(x, t)), s),b);
}
function md5_ff(a, b, c, d, x, s, t)
{
  return md5_cmn((b & c) | ((~b) & d), a, b, x, s, t);
}
function md5_gg(a, b, c, d, x, s, t)
{
  return md5_cmn((b & d) | (c & (~d)), a, b, x, s, t);
}
function md5_hh(a, b, c, d, x, s, t)
{
  return md5_cmn(b ^ c ^ d, a, b, x, s, t);
}
function md5_ii(a, b, c, d, x, s, t)
{
  return md5_cmn(c ^ (b | (~d)), a, b, x, s, t);
}

/*
 * Add integers, wrapping at 2^32. This uses 16-bit operations internally
 * to work around bugs in some JS interpreters.
 */
function safe_add(x, y)
{
  var lsw = (x & 0xFFFF) + (y & 0xFFFF);
  var msw = (x >> 16) + (y >> 16) + (lsw >> 16);
  return (msw << 16) | (lsw & 0xFFFF);
}

/*
 * Bitwise rotate a 32-bit number to the left.
 */
function bit_rol(num, cnt)
{
  return (num << cnt) | (num >>> (32 - cnt));
}

(function ($) {
	function widget(element, options) {
		this.element = element;
		this.options = options;
	}
	
	widget.prototype = (function() {
		
		function _widgetRun(widget) {
			if (!widget.options) {
				widget.element.append('<span class="error">Options for widget are not set.</span>');
				return;
			}
		
			var element = widget.element;
			var user = widget.options.user;
			var repo = widget.options.repo;
			var branch = widget.options.branch;
			var last = widget.options.last == undefined ? 0 : widget.options.last;
			var limitMessage = widget.options.limitMessageTo == undefined ? 0 : widget.options.limitMessageTo;
			
			gh.commit.forBranch(user, repo, branch, function (data) {
			  var commits = data.commits;
				var totalCommits = (last < commits.length ? last : commits.length);
				element.empty();
				element.append('<ul>');
				
				for (var c = 0; c < totalCommits; c++) {
					element.append(
						'<li>' +
						message(commits[c].message, commits[c].url) + 
						' by' + 
						' ' + avatar(commits[c].author.email) +
						' ' + author(commits[c].author.login) + 
						'</li>');
				}
				element.append('</ul>');
				
				function avatar(email) {
					var emailHash = hex_md5(email);
					return '<img src="http://www.gravatar.com/avatar/' + emailHash + '?s=20" style="border: white 1px solid;" />';
				}
				
				function author(login) {
					return '<a href="https://github.com/' + login + '">' + login + '</a>';
				}
				
				function message(commitMessage, url) {
					if (limitMessage > 0 && commitMessage.length > limitMessage)
					{
						commitMessage = commitMessage.substr(0, limitMessage) + '...';
					}
					return '<a href="https://github.com' + url + '">' + commitMessage + '</a>';
				}
				
				function when(commitDate) {
					var commitTime = new Date(commitDate).getTime();
					var todayTime = new Date().getTime();
					
					var differenceInDays = Math.floor(((todayTime - commitTime)/(24*3600*1000)));
					if (differenceInDays == 0) {
						var differenceInHours = Math.floor(((todayTime - commitTime)/(3600*1000)));
						if (differenceInHours == 0) {
							var differenceInMinutes = Math.floor(((todayTime - commitTime)/(600*1000)));
							if (differenceInMinutes == 0) {
								
								return 'just now';
							}
							
							return 'about ' + differenceInMinutes + ' minutes ago';
						}
						
						return 'about ' + differenceInHours + ' hours ago';
					}
					
					return differenceInDays + ' days ago';
				}
			});
		}
		
		return {
			run: function () {
				_widgetRun(this);
			}
		};
		
	})();

	$.fn.githubInfoWidget = function(options) {
		var w = new widget(this, options);
		w.run();
		
		return this;
	}
	
})(jQuery);
