/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartGlobal>
#include <QtCore/QHash>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGraphicsLinearLayout;
class QGraphicsRectItem;
class QGraphicsScene;
class QGraphicsWidget;
QT_END_NAMESPACE

class View;
class Chart;
class Grid;

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


class Window: public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(const QVariantHash &parameters, QWidget *parent = 0);
    ~Window();

private Q_SLOTS:
    void updateUI();
    void handleGeometryChanged();
    void handleChartSelected(QChart *chart);
private:
    QComboBox *createViewBox();
    QComboBox *createThemeBox();
    QComboBox *createAnimationBox();
    QComboBox *createLegendBox();
    QComboBox *createTempleteBox();
    void connectSignals();
    void createProxyWidgets();
    void comboBoxFocused(QComboBox *combox);
    inline void checkAnimationOptions();
    inline void checkView();
    inline void checkLegend();
    inline void checkOpenGL();
    inline void checkTheme();
    inline void checkState();
    inline void checkTemplate();
    inline void checkXTick();
    inline void checkYTick();
    inline void checkMinorXTick();
    inline void checkMinorYTick();
    QMenu *createMenu();
    QAction *createMenuAction(QMenu *menu, const QIcon &icon, const QString &text, const QVariant &data);
    void initializeFromParamaters(const QVariantHash &parameters);

private:
    QGraphicsScene *m_scene;
    View *m_view;
    QHash<QString, QGraphicsProxyWidget *> m_widgetHash;

    QGraphicsWidget *m_form;
    QComboBox *m_themeComboBox;
    QSpinBox *m_xTickSpinBox;
    QSpinBox *m_yTickSpinBox;
    QSpinBox *m_minorXTickSpinBox;
    QSpinBox *m_minorYTickSpinBox;
    QCheckBox *m_antialiasCheckBox;
    QComboBox *m_animatedComboBox;
    QComboBox *m_legendComboBox;
    QComboBox *m_templateComboBox;
    QComboBox *m_viewComboBox;
    QCheckBox *m_openGLCheckBox;
    QCheckBox *m_zoomCheckBox;
    QCheckBox *m_scrollCheckBox;
    QGraphicsLinearLayout *m_baseLayout;
    QMenu *m_menu;
    int m_template;
    Grid *m_grid;
    QString m_category;
    QString m_subcategory;
    QString m_name;

    friend class ComboBox;
};

class ComboBox: public QComboBox
{
public:
    ComboBox(Window *window, QWidget *parent = 0): QComboBox(parent), m_window(window)
    {}

protected:
    void focusInEvent(QFocusEvent *e) {
        QComboBox::focusInEvent(e);
        m_window->comboBoxFocused(this);
    }
private:
    Window *m_window;
};

#endif
