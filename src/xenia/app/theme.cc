/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#include "theme.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDirIterator>

namespace xe {
namespace app {

ThemeStatus Theme::LoadTheme() {
  if (directory_.isNull() || directory_.isEmpty()) {
    return THEME_NOT_FOUND;
  }

  if (!config_.LoadFromFile(directory_ + "/theme.json")) {
    return THEME_MISCONFIGURED;  // also happens if json file is missing
  }
  return THEME_LOAD_OK;
}

QString Theme::StylesheetForComponent(const QString &component) {
  // component has already been processed and stored
  if (styles_.find(component) != styles_.end()) {
    return styles_.value(component);
  }

  // style has yet to be cached, do it now
  const QString preprocessed_style = PreprocessStylesheet(component);
  return *styles_.insert(component, preprocessed_style);
}

QString Theme::PreprocessStylesheet(QString filename) {
  filename += ".css";
  QString qss_dir = directory_ + "/stylesheets/";
  QFile file;
  file.setFileName(qss_dir + filename);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return QString::null;  // TODO: better error handling
  }

  QString style = file.readAll();
  style.remove(QRegExp("[\\n\\t\\r]"));

  for (const auto &color : config_.colors()) {
    QString macro = color.first;
    macro.insert(0, '$');  // TODO: allow macro symbol to be changed
    style.replace(macro, color.second.name());
  }

  return style;
}

}  // namespace app
}  // namespace xe
