#include <gtest/gtest.h>
#include "quality_service.h"

class QualityServiceTest : public ::testing::Test {
protected:
    QualityService service;
};

TEST_F(QualityServiceTest, GradeBoundaries) {
    EXPECT_EQ(service.calculateGrade(90), "A");
    EXPECT_EQ(service.calculateGrade(80), "B");
    EXPECT_EQ(service.calculateGrade(70), "C");
    EXPECT_EQ(service.calculateGrade(60), "D");
    
}

TEST_F(QualityServiceTest, DiscountBoundaries) {
    EXPECT_EQ(service.calculateDiscount({1000, false, "", false, 12}), 20);
    EXPECT_EQ(service.calculateDiscount({-1, false, "", false, 12}), -1);
}

TEST_F(QualityServiceTest, DiscountCombinationRules) {
    EXPECT_EQ(service.calculateDiscount({600, true, "SAVE10", false, 12}), 35);
    EXPECT_EQ(service.calculateDiscount({600, true, "SAVE10", true, 22}), 35);
}

TEST_F(QualityServiceTest, BookingRules) {
    EXPECT_FALSE(service.canBookSeats({7, true, 150, false}));
    EXPECT_FALSE(service.canBookSeats({3, false, 10, true}));
}

TEST_F(QualityServiceTest, UsernameRules) {
    EXPECT_EQ(service.formatUsername("   "), "Ugyldig");
}

TEST_F(QualityServiceTest, SensorAverageUsesPreciseDivision) {
    EXPECT_DOUBLE_EQ(service.calculateSensorAverage({1, 2}), 1.5);
    EXPECT_DOUBLE_EQ(service.calculateSensorAverage({10, 11, 12}), 11.0);
}

TEST_F(QualityServiceTest, SensorHealthDetectsWarningAndUnstable) {
    EXPECT_EQ(service.evaluateSensorHealth({10, 15, 20}), "WARNING");
    EXPECT_EQ(service.evaluateSensorHealth({20, 70, 21}), "UNSTABLE");
    EXPECT_EQ(service.evaluateSensorHealth({10, 20, 110}), "ERROR");
}
