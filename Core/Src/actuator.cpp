#include "actuator.h"
#include "main.h"
#include "joystick.h"
#include "robo_init.h"
#include "motor.h"
#include "array.h"

extern motor gMotor[4];
static float velocity_robot[3] = {0, 0, 0};
uint32_t time = HAL_GetTick();

float velocity = 30;
extern JoyStick joystick;
void play(void)
{
     HAL_GPIO_WritePin(ledOrange_GPIO_Port, ledOrange_Pin, GPIO_PIN_SET);
    // forward();
    if ((HAL_GetTick() - time) >= 10)
    {
        // printf("hELLO HAL GET TICK %ld",time);

        // HAL_GPIO_WritePin(ledRed_GPIO_P0ort, ledRed_Pin, GPIO_PIN_SET);
        // HAL_GPIO_WritePin(ledGreen_GPIO_Port, ledGreen_Pin, GPIO_PIN_RESET);

        time = HAL_GetTick();
        Robot_task();
    }
}

void calculate_wheel_velocity()
{
    float velocity_motor[4] = {0, 0, 0, 0};
    float coupling_matrix[4][3] = {{0.707, -0.707, 1},
                                   {-0.707, -0.707, 1},
                                   {-0.707, 0.707, 1},
                                   {0.707, 0.707, 1}};

    for (int i = 0; i < 4; i++)
    {
        velocity_motor[i] = 0;
        for (int j = 0; j < 3; j++)
        {
            velocity_motor[i] += velocity_robot[j] * coupling_matrix[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        // printf("set motor velocity %f \n", velocity_motor[i]);
        gMotor[i].motor_input(velocity_motor[i], get_data(i)); //pid
    }
}

void forward()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = -velocity;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void back()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = +velocity;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void left()
{
    velocity_robot[0] = -velocity;
    velocity_robot[1] = 0;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void right()
{
    velocity_robot[0] = velocity;
    velocity_robot[1] = 0;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void forward_right()
{
    velocity_robot[0] = velocity / 2;
    velocity_robot[1] = -velocity / 2;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void forward_left()
{
    velocity_robot[0] = -velocity / 2;
    velocity_robot[1] = -velocity / 2;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void back_right()
{
    velocity_robot[0] = velocity / 2;
    velocity_robot[1] = velocity / 2;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void back_left()
{
    velocity_robot[0] = -velocity / 2;
    velocity_robot[1] = velocity / 2;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void clockwise()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = 0;
    velocity_robot[2] = 9;
    calculate_wheel_velocity();
}

void anticlockwise()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = 0;
    velocity_robot[2] = -9;
    calculate_wheel_velocity();
}

void stop()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = 0;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void set_Omega(float get_Velocity)
{
    velocity = get_Velocity;
}
