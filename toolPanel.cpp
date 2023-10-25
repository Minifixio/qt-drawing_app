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

    // Groupe de boutons radio pour sélectionner le style de la ligne
    QGroupBox* lineStyleGroup = new QGroupBox("Style de ligne", this);
    QRadioButton* solidRadioButton = new QRadioButton("Plein", this);
    QRadioButton* dashedRadioButton = new QRadioButton("Pointillé", this);
    QButtonGroup* lineStyleButtonGroup = new QButtonGroup(this);
    lineStyleButtonGroup->addButton(solidRadioButton);
    lineStyleButtonGroup->addButton(dashedRadioButton);

    solidRadioButton->setChecked(true);

    // Créez un groupe de boutons radio pour sélectionner la forme
    QGroupBox* shapeGroup = new QGroupBox("Forme", this);
    QRadioButton* lineRadioButton = new QRadioButton("Ligne",this);
    QRadioButton* rectangleRadioButton = new QRadioButton("Rectangle", this);
    QRadioButton* triangleRadioButton = new QRadioButton("Triangle", this);
    QRadioButton* ellipseRadioButton = new QRadioButton("Ellipse",this);
    QButtonGroup* shapeButtonGroup = new QButtonGroup(this);
    shapeButtonGroup->addButton(lineRadioButton,0);
    shapeButtonGroup->addButton(rectangleRadioButton,1);
    shapeButtonGroup->addButton(triangleRadioButton,2);
    shapeButtonGroup->addButton(ellipseRadioButton,3);

    // Appliquez une feuille de style pour augmenter la taille des icônes
    QString iconSizeStyle = "QRadioButton::indicator { width: 32px; height: 32px; }";
    lineRadioButton->setStyleSheet(iconSizeStyle);
    rectangleRadioButton->setStyleSheet(iconSizeStyle);
    triangleRadioButton->setStyleSheet(iconSizeStyle);
    ellipseRadioButton->setStyleSheet(iconSizeStyle);

    // Créez des icônes pour chaque forme (remplacez les chemins d'accès par les vôtres)
    QIcon lineIcon(":/tools/line.png");
    QIcon rectangleIcon(":/tools/rectangle.png");
    QIcon triangleIcon(":/tools/triangle.png");
    QIcon ellipseIcon(":/tools/ellipse.png");

    // Définissez les icônes pour les boutons radio
    lineRadioButton->setIcon(lineIcon);
    rectangleRadioButton->setIcon(rectangleIcon);
    triangleRadioButton->setIcon(triangleIcon);
    ellipseRadioButton->setIcon(ellipseIcon);

    // Créez un layout pour organiser les boutons radio
    QVBoxLayout* shapeLayout = new QVBoxLayout;
    shapeLayout->addWidget(lineRadioButton);
    shapeLayout->addWidget(rectangleRadioButton);
    shapeLayout->addWidget(triangleRadioButton);
    shapeLayout->addWidget(ellipseRadioButton);
    shapeGroup->setLayout(shapeLayout);

    lineRadioButton->setChecked(true);

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
    layout->addWidget(lineStyleGroup);
    layout->addLayout(thicknessLayout);
    layout->addWidget(colorButton);
    layout->addWidget(colorDisplay);
    layout->addWidget(shapeGroup);

    connect(colorButton, &QPushButton::clicked, this, &ToolPanel::chooseColor);
    connect(thicknessSlider, &QSlider::valueChanged, this, &ToolPanel::handleThicknessChanged);
    connect(dashedRadioButton, &QRadioButton::toggled, this, &ToolPanel::handleLineStyleChanged);
    connect(shapeButtonGroup, &QButtonGroup::idClicked, this, &ToolPanel::selectShape);

    setLayout(layout);
}

void ToolPanel::selectShape(int shapeId)
{
    qDebug() << "Shape id selected :" <<shapeId;

    switch(shapeId) {
    case 0:
        currentShape = Line;
        emit shapeSelected(currentShape);
        break;
    case 1:
        currentShape = Rectangle;
        emit shapeSelected(currentShape);
        break;
    case 2:
        currentShape = Triangle;
        emit shapeSelected(currentShape);
        break;
    case 3:
        currentShape = Ellipse;
        emit shapeSelected(currentShape);
        break;
    default:
        qDebug() << "Shape id selected is wrong :" <<shapeId;
    }
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

