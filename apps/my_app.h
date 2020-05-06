// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/Audio.h>
#include <pretzel/PretzelGui.h>
#include <mylibrary/leaderboard.h>
#include <mylibrary/player.h>

namespace myapp {

enum class GameState {
    kPlaying,
    kGameOver,
};

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

private:
    mylibrary::LeaderBoard leaderboard_;
    const std::string player_name_;
    GameState state_;
    std::vector<mylibrary::Player> top_players_;
    bool printed_game_over_;
    size_t time_left_;

private:
    void DrawBackground() const;
    void DrawGameOver();
    void DrawScore() const;
    void DrawNet() const;
    void DrawBall() const;
    void DrawPaddleOne() const;
    void DrawPaddleTwo() const;
    void UpdateBall();

private:
    int paddle1_score_ = 0;
    int paddle2_score_ = 0;

    float ball_radius = 10;
    float ball_xpos = getWindowWidth()/2;
    float ball_ypos = getWindowHeight()/2;
    float ball_xdir = -1.0f;
    float ball_ydir = 1.0f;
    int ball_speed = 8;

    float paddle1_x1 = getWindowWidth()/1.06f-5;
    float paddle1_y1 = getWindowHeight()/2-40.0f;
    float paddle1_x2 = getWindowWidth()/1.06f+5;
    float paddle1_y2 = getWindowHeight()/2+40.0f;

    float paddle2_x1 = getWindowWidth()/20.0f-5;
    float paddle2_y1 = getWindowHeight()/2-40.0f;
    float paddle2_x2 = getWindowWidth()/20.0f+5;
    float paddle2_y2 = getWindowHeight()/2+40.0f;

    cinder::audio::SourceFileRef bgm = cinder::audio::load(cinder::app::loadAsset("Pong.wav"));
    cinder::audio::VoiceRef play_bgm = cinder::audio::Voice::create(bgm);

    pretzel::PretzelGuiRef gui;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
