#pragma once

#include <string>

#include <QApplication>
#include <QWidget>

#ifdef QCOM2
#include <qpa/qplatformnativeinterface.h>
#include <wayland-client-protocol.h>
#include <QPlatformSurfaceEvent>
#endif

#include "selfdrive/hardware/hw.h"

#ifdef USE_QRC
const QString ASSET_PATH = ":/";
#else
const QString ASSET_PATH = "../assets/";
#endif

const int vwp_w = (Hardware::TICI() || (getenv("WIDE_UI") != NULL)) ? 2160 : 1920;
const int vwp_h = 1080;

void setMainWindow(QWidget *w);
