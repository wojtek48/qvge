/*
This file is a part of
QVGE - Qt Visual Graph Editor

(c) 2016-2019 Ars L. Masiuk (ars.masiuk@gmail.com)

It can be used freely, maintaining the information above.
*/

#ifndef CNODEPROPERTIESUI_H
#define CNODEPROPERTIESUI_H

#include <QWidget>
#include <QVariant>
#include <QSettings>

class CEditorScene;
class CNodeEditorScene;
class CNode;
class CDirectEdge;


namespace Ui {
class CNodeEdgePropertiesUI;
}

class CNodeEdgePropertiesUI : public QWidget
{
    Q_OBJECT

public:
    explicit CNodeEdgePropertiesUI(QWidget *parent = 0);
    ~CNodeEdgePropertiesUI();

    void setScene(CNodeEditorScene* scene);

	void doReadSettings(QSettings& settings);
	void doWriteSettings(QSettings& settings);

public Q_SLOTS:
	void updateFromScene(CEditorScene* scene);

protected:
    void connectSignals(CEditorScene* scene);
    void onSceneAttached(CEditorScene* scene);
    void onSceneDetached(CEditorScene* scene);

protected Q_SLOTS:
    void onSceneChanged();
    void onSelectionChanged();

    void on_NodeColor_activated(const QColor &color);
    void on_NodeFlowShape_activated(QVariant data);
    void on_NodeProcShape_activated(QVariant data);
    void on_NodeSizeX_valueChanged(int value);
	void on_StrokeColor_activated(const QColor &color);
	void on_StrokeStyle_activated(QVariant data);
	void on_StrokeSize_valueChanged(double value);
    void on_EdgeColor_activated(const QColor &color);
    void on_EdgeWeight_valueChanged(double value);
    void on_EdgeStyle_activated(QVariant data);
    void on_Edge_activated(QVariant data);
	void on_EdgeDirection_activated(QVariant data);

    void on_LabelFont_activated(const QFont &font);
	void on_LabelColor_activated(const QColor &color);
	void on_LabelFontSize_valueChanged(int value);
	void on_LabelFontBold_toggled(bool on);
	void on_LabelFontItalic_toggled(bool on);
	void on_LabelFontUnderline_toggled(bool on);

private slots:
    void on_NodeFlowShape_windowIconChanged(const QIcon &icon);

private:
	void setNodesAttribute(const QByteArray& attrId, const QVariant& v);
	void setEdgesAttribute(const QByteArray& attrId, const QVariant& v);

    CNodeEditorScene *m_scene;
    bool m_updateLock;

	CNode *m_nodeFactory;
	CDirectEdge *m_edgeFactory;

    Ui::CNodeEdgePropertiesUI *ui;
};

#endif // CNODEPROPERTIESUI_H
