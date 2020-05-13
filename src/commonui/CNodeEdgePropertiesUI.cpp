/*
This file is a part of
QVGE - Qt Visual Graph Editor

(c) 2016-2019 Ars L. Masiuk (ars.masiuk@gmail.com)

It can be used freely, maintaining the information above.
*/

#include <QInputDialog>
#include <QMessageBox>

#include "CAttributesEditorUI.h"
#include "CPropertyEditorUIBase.h"
#include "CNodeEdgePropertiesUI.h"
#include "ui_CNodeEdgePropertiesUI.h"

#include <qvge/CNodeEditorScene.h>
#include <qvge/CNode.h>
#include <qvge/CEdge.h>
#include <qvge/CDirectEdge.h>
#include <qvge/CAttribute.h>
#include <qvge/CEditorSceneDefines.h>
#include <Const.h>
#include <qvge/currentvalues.h>



CNodeEdgePropertiesUI::CNodeEdgePropertiesUI(QWidget *parent) :
    QWidget(parent),
    m_scene(NULL),
    m_updateLock(false),
    ui(new Ui::CNodeEdgePropertiesUI)
{
	m_nodeFactory = new CNode;
	m_edgeFactory = new CDirectEdge;


    ui->setupUi(this);

    //WPaw - dodawanie ikon nodów

    ui->NodeProcShape->addAction(QIcon(":/Icons/Icons/komponenty/bankDanych.PNG"), cBankDanych, cBankDanych);
    ui->NodeProcShape->addAction(QIcon(":/Icons/Icons/komponenty/harmonogram.PNG"), cHarmonogram, cHarmonogram);
    ui->NodeProcShape->addAction(QIcon(":/Icons/Icons/komponenty/generatorZdarzen.PNG"), cGeneratorZdarzen, cGeneratorZdarzen);
    ui->NodeProcShape->addAction(QIcon(":/Icons/Icons/komponenty/procedury.PNG"), cProcedury, cProcedury);
    ui->NodeProcShape->addAction(QIcon(":/Icons/Icons/komponenty/zasobStatyczny.PNG"), cZasobStatyczny, cZasobStatyczny);
    ui->NodeProcShape->addAction(QIcon(":/Icons/Icons/komponenty/zegar.PNG"), cZegar, cZegar);

    ui->NodeFlowShape->addAction(QIcon(":/Icons/Icons/komponenty/kompUniwersalny.PNG"), cKompUniwersalny, cKompUniwersalny);
    ui->NodeFlowShape->addAction(QIcon(":/Icons/Icons/komponenty/kompPrzetwarzania.PNG"), cKompPrzetwarzania, cKompPrzetwarzania);
    ui->NodeFlowShape->addAction(QIcon(":/Icons/Icons/komponenty/kompPrzeplywu.PNG"), cKompPrzeplywu, cKompPrzeplywu);
    ui->NodeFlowShape->addAction(QIcon(":/Icons/Icons/komponenty/kompWymuszPrzeplyw.PNG"), cKompWymuszPrzeplywu, cKompWymuszPrzeplywu);
    ui->NodeFlowShape->addAction(QIcon(":/Icons/Icons/komponenty/zrodloZasobu.PNG"), cZrodloZasobu, cZrodloZasobu);
    ui->NodeFlowShape->addAction(QIcon(":/Icons/Icons/komponenty/celZasobu.PNG"), cCelZasobu, cCelZasobu);


//	ui->EdgeDirection->addAction(QIcon(":/Icons/Edge-Directed"), tr("Directed (one end)"), "directed");
//	ui->EdgeDirection->addAction(QIcon(":/Icons/Edge-Mutual"), tr("Mutual (both ends)"), "mutual");
//	ui->EdgeDirection->addAction(QIcon(":/Icons/Edge-Undirected"), tr("None (no ends)"), "undirected");

//    ui->EdgeColor->setColorScheme(QSint::OpenOfficeColors());
    //ui->EdgeStyle->setUsedRange(Qt::SolidLine, Qt::DashDotDotLine);


    ui->Edge->addAction (QIcon(cIkonaKanalZdarzen), cKanalZdarzen, cKanalZdarzen);
    ui->Edge->addAction (QIcon(cIkonaKanalZasobu), cKanalZasobu, cKanalZasobu);
    ui->Edge->addAction (QIcon(cIkonaKanalDanych), cKanalDanych, cKanalDanych);
    ui->Edge->addAction (QIcon(cIkonaKanalKomunikacyjny), cKanalKomunikacyjny, cKanalKomunikacyjny);
    ui->Edge->addAction (QIcon(cIkonaProceduryWbudowane), cProceduryWbudowane, cProceduryWbudowane);
    ui->Edge->addAction (QIcon(cIkonaDostepnoscZasobu), cDostepnoscZasobu, cDostepnoscZasobu);

	// font size
	QList<int> fontSizes = { 5,6,7,8,9,10,11,12,14,16,18,20,24,28,32,36,40,44,48,54,60,66,72,80,88,96 };
	ui->LabelFontSize->setValueList(fontSizes);


	// node size
	QList<int> nodeSizes = { 5,10,15,20,30,40,50,75,100,150,200 };
	ui->NodeSizeX->setValueList(nodeSizes);


    // update status & tooltips etc.
    ui->retranslateUi(this);
    

}


CNodeEdgePropertiesUI::~CNodeEdgePropertiesUI()
{
	delete m_nodeFactory;
    delete ui;
}


void CNodeEdgePropertiesUI::doReadSettings(QSettings& settings)
{
	int pos = settings.value("nodes/splitterPosition", -1).toInt();

	/*int*/ pos = settings.value("edges/splitterPosition", -1).toInt();
}


void CNodeEdgePropertiesUI::doWriteSettings(QSettings& settings)
{
}


void CNodeEdgePropertiesUI::setScene(CNodeEditorScene* scene)
{
    if (m_scene)
        onSceneDetached(m_scene);

    m_scene = scene;

    setEnabled(m_scene);

    if (m_scene)
        onSceneAttached(m_scene);
}


void CNodeEdgePropertiesUI::connectSignals(CEditorScene* scene)
{
    connect(scene, SIGNAL(sceneChanged()), this, SLOT(onSceneChanged()));
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
}


void CNodeEdgePropertiesUI::updateFromScene(CEditorScene* scene)
{
	// default attrs
	auto nodeAttrs = scene->getClassAttributes("node", false);
    ui->NodeFlowShape->selectAction(nodeAttrs["shape"].defaultValue);

	QSize size = nodeAttrs["size"].defaultValue.toSize();
	ui->NodeSizeX->setValue(size.width());


	auto edgeAttrs = scene->getClassAttributes("edge", false);
//	ui->EdgeColor->setColor(edgeAttrs["color"].defaultValue.value<QColor>());
//	ui->EdgeWeight->setValue(edgeAttrs["weight"].defaultValue.toDouble());
//	ui->EdgeStyle->setPenStyle(CUtils::textToPenStyle(edgeAttrs["style"].defaultValue.toString()));
    //ui->EdgeDirection->selectAction(edgeAttrs["direction"].defaultValue);

	QFont f(edgeAttrs["label.font"].defaultValue.value<QFont>());
	ui->LabelFont->setCurrentFont(f);
	ui->LabelFontSize->setValue(f.pointSize());
	ui->LabelColor->setColor(edgeAttrs["label.color"].defaultValue.value<QColor>());
}


void CNodeEdgePropertiesUI::onSceneAttached(CEditorScene* scene)
{
	// factories for new items
	//scene->setActiveItemFactory(m_nodeFactory);
	//scene->setActiveItemFactory(m_edgeFactory);

	// default attrs
	updateFromScene(scene);

	// connect & go
    connectSignals(scene);

    onSceneChanged();
}


void CNodeEdgePropertiesUI::onSceneDetached(CEditorScene* scene)
{
    scene->disconnect(this);
}


void CNodeEdgePropertiesUI::onSceneChanged()
{
    // update active selections if any
    onSelectionChanged();
}


void CNodeEdgePropertiesUI::onSelectionChanged()
{
    if (m_updateLock || m_scene == NULL)
        return;

    m_updateLock = true;

    QList<CEdge*> edges = m_scene->getSelectedEdges();
    QList<CNode*> nodes = m_scene->getSelectedNodes();


    // nodes
    ui->NodesBox->setTitle(tr("Selected components (%1)").arg(nodes.count()));

    if (nodes.count())
    {
        auto node = nodes.first();

        ui->NodeFlowShape->selectAction(node->getAttribute("shape"));
		
		QSize size = node->getAttribute("size").toSize();
		ui->NodeSizeX->setValue(size.width());

    }

    QList<CItem*> nodeItems;
    // edges
    ui->EdgesBox->setTitle(tr("Selected connections (%1)").arg(edges.count()));

    if (edges.count())
    {
        auto edge = edges.first();

 //       ui->EdgeColor->setColor(edge->getAttribute("color").value<QColor>());
//        ui->EdgeWeight->setValue(edge->getAttribute("weight").toDouble());
//		ui->EdgeStyle->setPenStyle(CUtils::textToPenStyle(edge->getAttribute("style").toString()));
//		ui->EdgeDirection->selectAction(edge->getAttribute("direction"));
    }

    QList<CItem*> edgeItems;
    for (auto item: edges) edgeItems << item;


    // labels
    QList<CItem*> itemList;
    for (auto edgeItem: edges) itemList << edgeItem;
    for (auto nodeItem: nodes) itemList << nodeItem;
    for (auto item: itemList)
    {
		QFont f(item->getAttribute("label.font").value<QFont>());
        ui->LabelFont->setCurrentFont(f);
		ui->LabelFontSize->setValue(f.pointSize());
		ui->LabelFontBold->setChecked(f.bold());
		ui->LabelFontItalic->setChecked(f.italic());
		ui->LabelFontUnderline->setChecked(f.underline());
		ui->LabelColor->setColor(item->getAttribute("label.color").value<QColor>());
        break;
    }

    // allow updates
    m_updateLock = false;
}


void CNodeEdgePropertiesUI::setNodesAttribute(const QByteArray& attrId, const QVariant& v)
{
    QString s = QVariant(v).toString();
    if (attrId == "shape")
      CurrentValues::instance().shape = s;
	if (m_nodeFactory)
		m_nodeFactory->setAttribute(attrId, v);

	if (m_updateLock || m_scene == NULL)
		return;

	QList<CNode*> nodes = m_scene->getSelectedNodes();
	if (nodes.isEmpty())
		return;

    //WPaw - tu ustawia się atrybut dla konkretnego noda   
	for (auto node : nodes)
		node->setAttribute(attrId, v);
    m_scene->addUndoState();
}


void CNodeEdgePropertiesUI::setEdgesAttribute(const QByteArray& attrId, const QVariant& v)
{
	if (m_edgeFactory)
		m_edgeFactory->setAttribute(attrId, v);

	if (m_updateLock || m_scene == NULL)
		return;

	QList<CEdge*> edges = m_scene->getSelectedEdges();
	if (edges.isEmpty())
		return;

	for (auto edge : edges)
		edge->setAttribute(attrId, v);

	m_scene->addUndoState();
}


void CNodeEdgePropertiesUI::on_NodeColor_activated(const QColor &color)
{
	setNodesAttribute("color", color);
}


void CNodeEdgePropertiesUI::on_NodeFlowShape_activated(QVariant data)
{
	setNodesAttribute("shape", data);
    ui->rButFlow->setChecked(1);
//    ui->rButFlow->clicked(true);
//    ui->rButProc->clicked(false);
}

void CNodeEdgePropertiesUI::on_NodeProcShape_activated(QVariant data)
{
    setNodesAttribute("shape", data);
    ui->rButProc->setChecked(1);
//    ui->rButFlow->clicked(false);
//    ui->rButProc->clicked(true);
}


void CNodeEdgePropertiesUI::on_NodeSizeX_valueChanged(int /*value*/)
{
	ui->NodeSizeX->blockSignals(true);

    QSize size(ui->NodeSizeX->value(), ui->NodeSizeX->value());

	setNodesAttribute("size", size);

 	ui->NodeSizeX->blockSignals(false);
}

void CNodeEdgePropertiesUI::on_StrokeColor_activated(const QColor &color)
{
	setNodesAttribute("stroke.color", color);
}


void CNodeEdgePropertiesUI::on_StrokeStyle_activated(QVariant data)
{
	QString style = CUtils::penStyleToText(data.toInt());

	setNodesAttribute("stroke.style", style);
}


void CNodeEdgePropertiesUI::on_StrokeSize_valueChanged(double value)
{
	setNodesAttribute("stroke.size", value);
}


void CNodeEdgePropertiesUI::on_EdgeColor_activated(const QColor &color)
{
	setEdgesAttribute("color", color);
}


void CNodeEdgePropertiesUI::on_EdgeWeight_valueChanged(double value)
{
	setEdgesAttribute("weight", value);
}


void CNodeEdgePropertiesUI::on_EdgeStyle_activated(QVariant data)
{
	QString style = CUtils::penStyleToText(data.toInt());
	setEdgesAttribute("style", style);
}

void CNodeEdgePropertiesUI::on_Edge_activated(QVariant data)
{
    QString s = QVariant(data).toString();
    CurrentValues::instance().connection = s;
    setEdgesAttribute("style", data);
}

void CNodeEdgePropertiesUI::on_EdgeDirection_activated(QVariant data)
{
	setEdgesAttribute("direction", data);
}


void CNodeEdgePropertiesUI::on_LabelFont_activated(const QFont &font)
{
	ui->LabelFontSize->blockSignals(true);
	ui->LabelFontSize->setValue(font.pointSize());
	ui->LabelFontSize->blockSignals(false);

    if (m_updateLock || m_scene == NULL)
        return;

	QList<CItem*> items = m_scene->getSelectedNodesEdges();
	if (items.isEmpty())
		return;

	for (auto item : items)
	{
		item->setAttribute(attr_label_font, font);
	}

    m_scene->addUndoState();
}


void CNodeEdgePropertiesUI::on_LabelColor_activated(const QColor &color)
{
	if (m_updateLock || m_scene == NULL)
		return;

	QList<CItem*> items = m_scene->getSelectedNodesEdges();
	if (items.isEmpty())
		return;

	for (auto item : items)
	{
		item->setAttribute(attr_label_color, color);
	}

	m_scene->addUndoState();
}


void CNodeEdgePropertiesUI::on_LabelFontSize_valueChanged(int value)
{
	if (m_updateLock || m_scene == NULL)
		return;

	QList<CItem*> items = m_scene->getSelectedNodesEdges();
	if (items.isEmpty())
		return;

	bool set = false;

	for (auto item : items)
	{
		QFont font = item->getAttribute(attr_label_font).value<QFont>();
		if (font.pointSize() != value)
		{
			font.setPointSize(value);
			item->setAttribute(attr_label_font, font);
			set = true;
		}
	}

	if (set)
		m_scene->addUndoState();
}


void CNodeEdgePropertiesUI::on_LabelFontBold_toggled(bool on)
{
	if (m_updateLock || m_scene == NULL)
		return;

	QList<CItem*> items = m_scene->getSelectedNodesEdges();
	if (items.isEmpty())
		return;

	bool set = false;

	for (auto item : items)
	{
		QFont font = item->getAttribute(attr_label_font).value<QFont>();
		if (font.bold() != on)
		{
			font.setBold(on);
			item->setAttribute(attr_label_font, font);
			set = true;
		}
	}

	if (set)
		m_scene->addUndoState();
}


void CNodeEdgePropertiesUI::on_LabelFontItalic_toggled(bool on)
{
	if (m_updateLock || m_scene == NULL)
		return;

	QList<CItem*> items = m_scene->getSelectedNodesEdges();
	if (items.isEmpty())
		return;

	bool set = false;

	for (auto item : items)
	{
		QFont font = item->getAttribute(attr_label_font).value<QFont>();
		if (font.italic() != on)
		{
			font.setItalic(on);
			item->setAttribute(attr_label_font, font);
			item->updateLabelContent();
			set = true;
		}
	}

	if (set)
		m_scene->addUndoState();
}


void CNodeEdgePropertiesUI::on_LabelFontUnderline_toggled(bool on)
{
	if (m_updateLock || m_scene == NULL)
		return;

	QList<CItem*> items = m_scene->getSelectedNodesEdges();
	if (items.isEmpty())
		return;

	bool set = false;

	for (auto item : items)
	{
		QFont font = item->getAttribute(attr_label_font).value<QFont>();
		if (font.underline() != on)
		{
			font.setUnderline(on);
			item->setAttribute(attr_label_font, font);
			set = true;
		}
	}

	if (set)
		m_scene->addUndoState();
}



void CNodeEdgePropertiesUI::on_NodeFlowShape_windowIconChanged(const QIcon &icon)
{
    QMessageBox qmb;
    qmb.setText( " duuuap");
    qmb.exec();
}
