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

#ifndef WALLETNOTIFIER_H
#define WALLETNOTIFIER_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QString>


class WalletNotifier : public QWidget {

  Q_OBJECT
  Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

  void setPopupOpacity(float opacity);
  float getPopupOpacity() const;

  public:
    explicit WalletNotifier(QWidget *parent = 0);

  protected:
    void paintEvent(QPaintEvent *event);

  public slots:
    void pushNotification(const QString &text);
    void pushBeepMode(const bool beepEnable);
 
  private slots:
    void show();
    void hideAnimation();
    void hide();
 
  private:
    bool m_beepEnable;
    QLabel label;
    QGridLayout layout;
    QPropertyAnimation animation;
    float popupOpacity;
    QTimer *timer;

};

#endif

