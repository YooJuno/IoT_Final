#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <random>

using namespace std;
using namespace cv;

#define GRID_NUM 20 // 전체 맵을 가로, 세로 얼마나 쪼갤지 (GRID_NUM x GRID_NUM)

class Background
{
public:
    Background(int size)
        : _size(size)
    {
        set_array();
        game_map = Mat(size, size, CV_8UC3, Scalar(255, 153, 103));
        putText(game_map, "Wait For the User...", Point(500/2, 500/2), FONT_HERSHEY_SIMPLEX, 8, Scalar(255, 255, 255), 2);
        draw_background();
    }

    void draw_background()
    {
        game_map = Mat(_size, _size, CV_8UC3, Scalar(100, 100, 0));
        for (int i = 0; i < GRID_NUM; i++)
        {
            for (int j = 0; j < GRID_NUM; j++)
            {
                if (map_array[i][j])
                {
                    rectangle(game_map,
                              Rect(j * (_size / GRID_NUM), i * (_size / GRID_NUM), _size / GRID_NUM, _size / GRID_NUM),
                              Scalar(0, 0, 0),
                              FILLED);
                }

                if (dot_array[i][j])
                    circle(game_map, Point(j * (_size / GRID_NUM) + (_size / GRID_NUM) / 2, i * (_size / GRID_NUM) + (_size / GRID_NUM) / 2), 5, Scalar(97, 150, 242), 1, 8, 0);
            }
        }
    }

    bool is_inbound(int cur_x, int cur_y)
    {
        return map_array[cur_y / (_size / GRID_NUM)][cur_x / (_size / GRID_NUM)];
    }

    bool get_map_array(int j, int i)
    {
        return map_array[j][i];
    }

    void set_array()
    {

        for (int i = 0; i < GRID_NUM + 1; i++)
        {
            for (int j = 0; j < GRID_NUM + 1; j++)
            {
                if (map_array[j][i])
                    dot_array[j][i] = 1;
                else
                    dot_array[j][i] = 0;
            }
        }
    }

    Mat game_map;
    bool map_array[GRID_NUM + 1][GRID_NUM + 1] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    bool dot_array[GRID_NUM + 1][GRID_NUM + 1];

private:
    int _size;
};

class Pacman
{
public:
    Pacman(int size, Background &background, int id)
        : _size(size), background(background), id(id)
    {
        radius = min(_size / (GRID_NUM * 2), _size / (GRID_NUM * 2) );
        if(id==0){
            pose_x = radius;
            pose_y = radius;
        }
        else if(id==1){
            pose_x = radius;
            pose_y = _size-radius;
        }
        else if(id==2){
            pose_x = _size-radius;
            pose_y = radius;
        }
        else if(id==3){
            pose_x = _size-radius;
            pose_y = _size-radius;
        }
        direction_x = 0;
        direction_y = 0;
        offset = 2;
        angle_mouse = 0;
        point = 0;
    }

    void draw_packman()
    {
        Scalar pacmanColor;

        if (id == 0)
        {
            pacmanColor = Scalar(0, 255, 255); // Yellow color for Pacman 1
        }
        else if (id == 1)
        {
            pacmanColor = Scalar(0, 255, 0); // Green color for Pacman 2
        }
        else if (id == 2)
        {
            pacmanColor = Scalar(255, 255, 0); // Red color for Pacman 3
        }
        else if (id == 3)
        {
            pacmanColor = Scalar(255, 0, 255); // Purple color for Pacman 4
        }

        ellipse(background.game_map, Point(pose_x, pose_y), Size(radius, radius), 0, mouthAngle + angle_mouse, 360 - mouthAngle + angle_mouse, pacmanColor, -1);
        // Display score text
        std::string scoreText = "[" + std::to_string(id) + "] Score: " + std::to_string(point);
        putText(background.game_map, scoreText, Point(pose_x - 40, pose_y - 30), FONT_HERSHEY_SIMPLEX, 0.5, pacmanColor, 1);
    }

    void update_pose(int map_size)
    {
        if (direction_y == 1 && pose_y > radius)
        { // 위
            if (background.is_inbound(pose_x, pose_y - offset - radius) &&
                background.is_inbound(pose_x - radius, pose_y - offset - radius) &&
                background.is_inbound(pose_x + radius, pose_y - offset - radius))
                pose_y -= offset;
        }
        else if (direction_y == -1 && pose_y < background.game_map.rows - radius)
        { // 아래
            if (background.is_inbound(pose_x, pose_y + offset + radius) &&
                background.is_inbound(pose_x - radius, pose_y + offset + radius) &&
                background.is_inbound(pose_x + radius, pose_y + offset + radius))
                pose_y += offset;
        }
        else if (direction_x == -1 && pose_x > radius)
        { // 왼쪽
            if (background.is_inbound(pose_x - offset - radius, pose_y) &&
                background.is_inbound(pose_x - offset - radius, pose_y - radius) &&
                background.is_inbound(pose_x - offset - radius, pose_y + radius))
                pose_x -= offset;
        }
        else if (direction_x == 1 && pose_x < background.game_map.cols - radius)
        { // 오른쪽
            if (background.is_inbound(pose_x + offset + radius, pose_y) &&
                background.is_inbound(pose_x + offset + radius, pose_y - radius) &&
                background.is_inbound(pose_x + offset + radius, pose_y + radius))
                pose_x += offset;
        }

        for (int i = 0; i < GRID_NUM; i++)
        {
            for (int j = 0; j < GRID_NUM; j++)
            {
                if (background.dot_array[j][i])
                {
                    if (pose_x >= i * (map_size / GRID_NUM) && pose_x < (i + 1) * (map_size / GRID_NUM))
                    {
                        if (pose_y >= j * (map_size / GRID_NUM) && pose_y < (j + 1) * (map_size / GRID_NUM))
                        {
                            point += 1;
                            background.dot_array[j][i] = 0;
                        }
                    }
                }
            }
        }
    }

    void update_direction(int key_val)
    {
        // 입 벌리고 닫기
        if (openMouth)
        {
            mouthAngle += 2;
            if (mouthAngle >= 60)
                openMouth = false;
        }
        else
        {
            mouthAngle -= 2;
            if (mouthAngle <= 0)
                openMouth = true;
        }
        // 입 방향 전환
        if (key_val == 'a' || key_val == 81)
        {
            direction_x = -1;
            direction_y = 0;
            angle_mouse = 180;
        }
        else if (key_val == 'd' || key_val == 83)
        {
            direction_x = 1;
            direction_y = 0;
            angle_mouse = 0;
        }
        else if (key_val == 'w' || key_val == 82)
        {
            direction_y = 1;
            direction_x = 0;
            angle_mouse = 270;
        }
        else if (key_val == 's' || key_val == 84)
        {
            direction_y = -1;
            direction_x = 0;
            angle_mouse = 90;
        }
    }

    int get_point() const
    {
        return point;
    }

private:
    int _size;
    int pose_x;
    int pose_y;
    int direction_x;
    int direction_y;
    int offset;
    int mouthAngle = 0;
    bool openMouth = true;
    int angle_mouse;
    int radius;
    int point;
    Background &background;
    int id;
};
