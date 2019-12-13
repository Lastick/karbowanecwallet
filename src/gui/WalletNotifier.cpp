// Copyright (c) 2019 The Karbowanec developers
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Code formatting based on CS106B Style

#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include "WalletNotifier.h"

 
WalletNotifier::WalletNotifier(QWidget *parent) : QWidget(parent) {
  setWindowFlags(Qt::FramelessWindowHint |
                 Qt::Tool |
                 Qt::WindowStaysOnTopHint);
  setAttribute(Qt::WA_TranslucentBackground);
  setAttribute(Qt::WA_ShowWithoutActivating);

  animation.setTargetObject(this);
  animation.setPropertyName("popupOpacity");
  connect(&animation, &QAbstractAnimation::finished, this, &WalletNotifier::hide);
 
  label.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  label.setStyleSheet("QLabel { color : #15315E; "
                      "font: normal 14px;"
                      "margin-top: 6px;"
                      "margin-bottom: 6px;"
                      "margin-left: 10px;"
                      "margin-right: 10px; }");

  layout.addWidget(&label, 0, 0);
  setLayout(&layout);

  timer = new QTimer();
  connect(timer, &QTimer::timeout, this, &WalletNotifier::hideAnimation);

  m_beepEnable = true;
}

void WalletNotifier::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QRect roundedRect;
  roundedRect.setX(rect().x() + 5);
  roundedRect.setY(rect().y() + 5);
  roundedRect.setWidth(rect().width() - 10);
  roundedRect.setHeight(rect().height() - 10);
  painter.setBrush(QBrush(QColor(133, 167, 211, 255)));
  painter.setPen(Qt::NoPen);

  painter.drawRoundedRect(roundedRect, 10, 10);
}

void WalletNotifier::pushNotification(const QString &text) {
  label.setText(text);
  adjustSize();
  show();
  if (m_beepEnable) QApplication::beep();
}

void WalletNotifier::pushBeepMode(const bool beepEnable) {
  m_beepEnable = beepEnable;
}

void WalletNotifier::show() {
  setWindowOpacity(0.0);
  animation.setDuration(150);
  animation.setStartValue(0.0);
  animation.setEndValue(1.0);

  setGeometry(QApplication::desktop()->availableGeometry().width() - 36 - width() + QApplication::desktop()->availableGeometry().x(),
              QApplication::desktop()->availableGeometry().height() - 36 - height() + QApplication::desktop()->availableGeometry().y(),
              width(),
              height());
  QWidget::show();

  animation.start();
  timer->start(10000);
}

void WalletNotifier::hideAnimation() {
  timer->stop();
  animation.setDuration(1000);
  animation.setStartValue(1.0);
  animation.setEndValue(0.0);
  animation.start();
}

void WalletNotifier::hide() {
  if (getPopupOpacity() == 0.0) QWidget::hide();
}

void WalletNotifier::setPopupOpacity(float opacity) {
  popupOpacity = opacity;
  setWindowOpacity(opacity);
}

float WalletNotifier::getPopupOpacity() const {
  return popupOpacity;
}

