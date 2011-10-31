#include "oclint/RuleConfigurationTest.h"

void RuleConfigurationTest::testAddConfiguration() {
  TS_ASSERT(!RuleConfiguration::hasKey("foo"));
  RuleConfiguration::addConfiguration("foo", "bar");
  TS_ASSERT(RuleConfiguration::hasKey("foo"));
  TS_ASSERT_EQUALS(RuleConfiguration::valueForKey("foo"), "bar");
  RuleConfiguration::removeAll();
  TS_ASSERT(!RuleConfiguration::hasKey("foo"));
}

void RuleConfigurationTest::testAddTwoConfigurations() {
  TS_ASSERT(!RuleConfiguration::hasKey("foo"));
  TS_ASSERT(!RuleConfiguration::hasKey("bar"));
  RuleConfiguration::addConfiguration("foo", "bar");
  TS_ASSERT(RuleConfiguration::hasKey("foo"));
  TS_ASSERT(!RuleConfiguration::hasKey("bar"));
  TS_ASSERT_EQUALS(RuleConfiguration::valueForKey("foo"), "bar");
  RuleConfiguration::addConfiguration("bar", "foo");
  TS_ASSERT(RuleConfiguration::hasKey("bar"));
  TS_ASSERT_EQUALS(RuleConfiguration::valueForKey("bar"), "foo");
  RuleConfiguration::removeAll();
  TS_ASSERT(!RuleConfiguration::hasKey("foo"));
  TS_ASSERT(!RuleConfiguration::hasKey("bar"));
}
