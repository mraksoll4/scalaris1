// Copyright (c) 2018-2019 The Blocknet developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/blockneticonbtn.h>

#include <qt/blocknetguiutil.h>

#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

BlocknetIconBtn::BlocknetIconBtn(const QString &title, const QString &img, QFrame *parent) : QFrame(parent),
                                                                                             hoverState(false),
                                                                                             iconLbl(nullptr)
{
//    this->setStyleSheet("border: 1px solid red");
    this->setCursor(Qt::PointingHandCursor);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QPixmap pm(img);
    pm.setDevicePixelRatio(BGU::dpr());

    icon = new QLabel(this);
    icon->setFixedHeight(BGU::spi(56));
    icon->setAlignment(Qt::AlignVCenter);
    icon->setPixmap(pm.scaledToHeight(icon->height(), Qt::SmoothTransformation));
    icon->show();

    if (!title.isEmpty()) {
        auto *layout = new QVBoxLayout;
        layout->setSizeConstraint(QLayout::SetFixedSize);
        this->setLayout(layout);
        iconLbl = new QLabel(title);
        iconLbl->setObjectName("title");
        iconLbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        iconLbl->setAlignment(Qt::AlignCenter);
        iconLbl->setWordWrap(true);
        iconLbl->setFixedWidth(BGU::spi(30));
        layout->addSpacing(BGU::spi(84));
        layout->addWidget(iconLbl);
    }

    this->adjustSize();
	auto sh = sizeHint();
    this->setFixedSize(sh.width(), sh.height());
}

BlocknetIconBtn::BlocknetIconBtn(const QString &img, QFrame *parent) : BlocknetIconBtn(QString(), img, parent) {}

QSize BlocknetIconBtn::sizeHint() const {
    if (iconLbl)
        return { BGU::spi(30),
                 iconLbl->height() + BGU::spi(1) };
    else
        return {BGU::spi(1), BGU::spi(1) };
}

void BlocknetIconBtn::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);

    const int linew = BGU::spi(2);
	const int linew2 = linew/2;
    auto w = static_cast<qreal>(this->width());

    QPainter p(this);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    QPen pen(QColor(0x74, 0xB2, 0xFE), linew, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen);
}

void BlocknetIconBtn::mouseReleaseEvent(QMouseEvent *event) {
    QWidget::mouseReleaseEvent(event);
    QRect rect(0, 0, this->width(), this->height());
    if (rect.intersects({static_cast<int>(event->localPos().x()), static_cast<int>(event->localPos().y()), 1, 1 }))
        Q_EMIT clicked();
}
