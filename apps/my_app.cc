// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <pretzel/PretzelGui.h>
#include <gflags/gflags.h>
#include <mylibrary/player.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <string>

namespace myapp {

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace std;

const size_t kLimit = 3;
const char kDbPath[] = "app.db";
#if defined(CINDER_COCOA_TOUCH)
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";
#endif

DECLARE_string(name);

MyApp::MyApp()
    : leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
    player_name_{FLAGS_name},
    printed_game_over_{false},
    state_{GameState::kPlaying},
    time_left_{0} {}

void MyApp::setup() {
    /*gui = pretzel::PretzelGui::create("Puzzle settings");
    gui->setSize(cinder::vec2(180, 150));
    gui->setPos(cinder::vec2(0, 0));
    gui->addSlider("Puzzle Size", &mRadius, 2, 100);
    gui->addSaveLoad();
    gui->loadSettings();
    ci::gl::enableAlphaBlending();*/
}

void MyApp::update() {
    if (state_ == GameState::kGameOver) {
        if (top_players_.empty()) {
            if (paddle1_score_ > paddle2_score_) {
                leaderboard_.AddScoreToLeaderBoard({player_name_, static_cast<size_t>(paddle1_score_)});
                top_players_ = leaderboard_.RetrieveHighScores(kLimit);
            } else if (paddle2_score_ > paddle1_score_) {
                leaderboard_.AddScoreToLeaderBoard({player_name_, static_cast<size_t>(paddle2_score_)});
                top_players_ = leaderboard_.RetrieveHighScores(kLimit);
            }
            assert(!top_players_.empty());
        }
        return;
    }

    if (ball_xpos < 0 || ball_xpos > getWindowWidth()) {
        state_ = GameState::kGameOver;
    }

    UpdateBall();
}

void MyApp::draw() {
    /*cinder::gl::clear(cinder::Color(1, 1, 1));
    cinder::gl::drawSolidCircle(cinder::vec2(getWindowCenter()), mRadius);
    gui->draw();*/

    if (state_ == GameState::kGameOver) {
        if (!printed_game_over_) {
            cinder::gl::clear(Color(1, 0, 0));
        }
        DrawGameOver();
        return;
    }

    cinder::gl::clear();
    DrawBackground();
    DrawScore();
    DrawNet();
    DrawBall();
    DrawPaddleOne();
    DrawPaddleTwo();
}

// taken from snake
void PrintText(const string& text, const Color& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
    cinder::gl::color(color);

    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font(kNormalFont, 30))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
}

void MyApp::DrawBackground() const {
    cinder::gl::clear(Color(0, 0, 0));
}

// taken from snake
void MyApp::DrawGameOver() {
    if (printed_game_over_) return;
    if (top_players_.empty()) return;

    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 50};
    const Color color = Color::white();

    size_t row = 0;
    PrintText("Game Over", color, size, center);
    for (const mylibrary::Player& player : top_players_) {
        std::stringstream ss;
        ss << player.name << " - " << player.score;
        PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
    }

    printed_game_over_ = true;
}

void MyApp::DrawScore() const {
    const Color color = Color::white();
    const cinder::ivec2 size = {500, 50};
    const cinder::vec2 center = getWindowCenter();
    PrintText(to_string(paddle1_score_), color, size, {center.x + 250, center.y - 200});
    PrintText(to_string(paddle2_score_), color, size, {center.x - 250, center.y - 200});
}

void MyApp::DrawNet() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawLine(cinder::vec2(getWindowWidth()/2, getWindowHeight()), cinder::vec2(getWindowWidth()/2, 0));
}

void MyApp::DrawBall() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidCircle(cinder::vec2(ball_xpos, ball_ypos), ball_radius);
}

void MyApp::DrawPaddleOne() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidRect(Rectf(paddle1_x1, paddle1_y1, paddle1_x2, paddle1_y2));
}

void MyApp::DrawPaddleTwo() const {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidRect(Rectf(paddle2_x1, paddle2_y1, paddle2_x2, paddle2_y2));
}

void MyApp::UpdateBall() {
    ball_xpos += ball_xdir * ball_speed;
    ball_ypos += ball_ydir * ball_speed;
    /*if (ball_xpos < 0) {
        ball_xpos = 0;
        ball_xdir = fabs(ball_xdir);
    }
    if (ball_xpos > getWindowWidth()) {
        ball_xpos = getWindowWidth();
        ball_xdir = -fabs(ball_xdir);
    }*/
    if (ball_ypos < 0) {
        ball_ypos = 0;
        ball_ydir = fabs(ball_ydir);
    }
    if (ball_ypos > getWindowHeight()) {
        ball_ypos = getWindowHeight();
        ball_ydir = -fabs(ball_ydir);
    }
    if (ball_xpos > paddle1_x1 && ball_ypos > paddle1_y1 && ball_xpos > paddle1_x2 && ball_ypos < paddle1_y2) {
        ball_xpos = paddle1_x1;
        paddle1_score_++;
        ball_xdir = -fabs(ball_xdir);
    }
    if (ball_xpos < paddle2_x1 && ball_ypos > paddle2_y1 && ball_xpos < paddle2_x2 && ball_ypos < paddle2_y2) {
        ball_xpos = paddle2_x2;
        paddle2_score_++;
        ball_xdir = fabs(ball_xdir);
    }
}

void MyApp::keyDown(KeyEvent event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_UP: {
            paddle1_y1 = paddle1_y1 - 50;
            paddle1_y2 = paddle1_y2 - 50;
            break;
        }
        case KeyEvent::KEY_DOWN: {
            paddle1_y1 = paddle1_y1 + 50;
            paddle1_y2 = paddle1_y2 + 50;
            break;
        }
        case KeyEvent::KEY_w: {
            paddle2_y1 = paddle2_y1 - 50;
            paddle2_y2 = paddle2_y2 - 50;
            break;
        }
        case KeyEvent::KEY_s: {
            paddle2_y1 = paddle2_y1 + 50;
            paddle2_y2 = paddle2_y2 + 50;
            break;
        }
    }
}

}  // namespace myapp
