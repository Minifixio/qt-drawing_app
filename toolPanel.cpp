#include "toolPanel.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QVBoxLayout>

ToolPanel::ToolPanel(QWidget *parent)
    : QWidget{parent}
{
    // Groupe de boutons radio pour sélectionner le type de dessin
    QGroupBox* drawingTypeGroup = new QGroupBox("Type de dessin", this);
    QRadioButton* lineRadioButton = new QRadioButton("Ligne", this);
    QRadioButton* shapeRadioButton = new QRadioButton("Formes", this);
    QButtonGroup* drawingTypeButtonGroup = new QButtonGroup(this);
    drawingTypeButtonGroup->addButton(lineRadioButton);
    drawingTypeButtonGroup->addButton(shapeRadioButton);

    // Groupe de boutons radio pour sélectionner le style de la ligne
    QGroupBox* lineStyleGroup = new QGroupBox("Style de ligne", this);
    QRadioButton* solidRadioButton = new QRadioButton("Plein", this);
    QRadioButton* dashedRadioButton = new QRadioButton("Pointillé", this);
    QButtonGroup* lineStyleButtonGroup = new QButtonGroup(this);
    lineStyleButtonGroup->addButton(solidRadioButton);
    lineStyleButtonGroup->addButton(dashedRadioButton);

    lineRadioButton->setChecked(true);
    solidRadioButton->setChecked(true);

    // Slider pour sélectionner l'épaisseur du trait
    QSlider* thicknessSlider = new QSlider(Qt::Horizontal, this);
    thicknessSlider->setRange(1, 10); // Réglez la plage d'épaisseur souhaitée
    thicknessSlider->setValue(1);

    thicknessLabel = new QLabel("Épaisseur : 1", this);
    QVBoxLayout* thicknessLayout = new QVBoxLayout;
    thicknessLayout->addWidget(thicknessSlider);
    thicknessLayout->addWidget(thicknessLabel, 0, Qt::AlignHCenter);

    QPushButton* colorButton = new QPushButton("Choisir une couleur", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    // Ajout des boutons radio au groupe de sélection de type de dessin
    QVBoxLayout* drawingTypeLayout = new QVBoxLayout(drawingTypeGroup);
    drawingTypeLayout->addWidget(lineRadioButton);
    drawingTypeLayout->addWidget(shapeRadioButton);
    drawingTypeGroup->setLayout(drawingTypeLayout);

    // Ajout des boutons radio au groupe de sélection de style de ligne
    QVBoxLayout* lineStyleLayout = new QVBoxLayout(lineStyleGroup);
    lineStyleLayout->addWidget(solidRadioButton);
    lineStyleLayout->addWidget(dashedRadioButton);
    lineStyleGroup->setLayout(lineStyleLayout);

    colorDisplay = new QFrame(this);
    colorDisplay->setFrameShape(QFrame::Box);
    colorDisplay->setFrameShadow(QFrame::Sunken); // Pour donner un effet enfoncé au contour
    colorDisplay->setMinimumSize(30, 30);
    colorDisplay->setStyleSheet("background-color: black;"); // Noir par défaut

    // Ajout les widgets au layout principal
    layout->addWidget(drawingTypeGroup);
    layout->addWidget(lineStyleGroup);
    layout->addWidget(colorButton);
    layout->addWidget(colorDisplay);
    layout->addLayout(thicknessLayout);

    connect(colorButton, &QPushButton::clicked, this, &ToolPanel::chooseColor);
    connect(thicknessSlider, &QSlider::valueChanged, this, &ToolPanel::handleThicknessChanged);

    connect(dashedRadioButton, &QRadioButton::toggled, this, &ToolPanel::handleLineStyleChanged);

    setLayout(layout);
}

void ToolPanel::handleThicknessChanged(int thickness)
{
    QString labelText = QString("Épaisseur : %1").arg(thickness);
    thicknessLabel->setText(labelText);
    emit thicknessChanged(thickness);
}

void ToolPanel::chooseColor()
{
    QColorDialog colorDialog;
    QColor selectedColor = colorDialog.getColor();
    if (selectedColor.isValid())
    {
        emit colorSelected(selectedColor);

        colorDisplay->setStyleSheet(QString("background-color: %1;").arg(selectedColor.name()));
    }
}

void ToolPanel::handleLineStyleChanged(bool dashed)
{
    if (dashed)
    {
        emit lineStyleChanged(Qt::DashLine);
    }
    else
    {
        emit lineStyleChanged(Qt::SolidLine);
    }
}

