// autons.cpp
#include "main.h"
#include "subsystems.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 100;
const int DRIVE_SPEED_SLOW = 30;
const int TURN_SPEED = 90;
const int TURN_SPEED_SLOW = 40;
const int SWING_SPEED = 60;

///
// Constants
///
void default_constants() {
  // All of the PID stuff you need to tweak
  //  P, I, D, and Start I
  chassis.pid_drive_constants_set(10, 0, 0);  // Fwd/rev constants, used for odom and non odom motions
  // 0.2, 0, 0.2 workedd
  chassis.pid_heading_constants_set(0.2, 0, 0);  // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(-1, 0, 1);      // Turn in place constants
  chassis.pid_swing_constants_set(0, 0, 0);      // Swing constants
  // Exit conditions
  chassis.pid_turn_exit_condition_set(40_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  // PID turning constants
  chassis.pid_turn_chain_constant_set(5_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);
  // Slew constants
  chassis.slew_turn_constants_set(5_deg, 70);  // should be 10deg changed temporarily
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 127);

  /*Odom stuff
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
  */
}

///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  // if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  // if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  // if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  // if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();

  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    // chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    // double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    //  double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    // double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    // double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    // double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    // l_offset += l_delta / t_delta;
    // r_offset += r_delta / t_delta;
    // b_offset += b_delta / t_delta;
    // f_offset += f_delta / t_delta;
  }

  // Average all offsets
  // l_offset /= iterations;
  // r_offset /= iterations;
  // b_offset /= iterations;
  // f_offset /= iterations;

  // Set new offsets to trackers that exist
  // if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  // if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  // if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  // if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

// . . .
// Make your own autonomous functions here!
// . . .

// make sure to make a function of your auton in autons.hpp you stupud dumb
// test auton
// ...existing code...
void brainPrint() {
  while (true) {
    master.clear();
    double heading = chassis.imu.get_heading();    // current bearing in degrees
    master.print(0, 0, "Heading: %.1f", heading);  // line 0, col 0 on controller screen
    pros::delay(100);                              // update every 100 ms
  }
}
// ...existing code...
void testAuton() {
  default_constants();
  // pros::Task brainPrintTask(brainPrint);

  chassis.pid_drive_set(28.3, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_behavior_set(ez::shortest);  // turn the shortest direction
  matchLoader.set(true);
  intakePiston.set(false);
  chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(10, DRIVE_SPEED_SLOW);  // coming up to match loader
  intake.move(127);
  preroller.move(127);
  chassis.pid_wait_until(3_in);
  pros::delay(5000);  // hold for a bit to let the balls settle in the match loader
  chassis.pid_wait_quick_chain();

  // second phase, drive to long goal and score then align with middle balls
  matchLoader.set(false);
  scoreMoter.move(127);
  intake.move(127);
  intakePiston.set(true);
  chassis.pid_drive_set(-15, DRIVE_SPEED_SLOW);  // back out of match loader
  chassis.pid_wait_quick_chain();
  pros::delay(5000);  // wait to score
  chassis.pid_drive_set(18, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-150, TURN_SPEED);  // turn around
  chassis.pid_wait_quick_chain();
  scoreMoter.move(0);
  // third phase, pick up middle balls, drive to top right match loader and score on that goal
  intakePiston.set(false);
  chassis.pid_drive_set(30, DRIVE_SPEED_SLOW);
  intake.move(127);
  preroller.move(127);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(30, DRIVE_SPEED_SLOW);
  intake.move(-127);
  preroller.move(-127);
  pros::delay(5000);  // wait to score
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-30, DRIVE_SPEED_SLOW); // back out of middle goal
  chassis.pid_wait_quick_chain();
}
