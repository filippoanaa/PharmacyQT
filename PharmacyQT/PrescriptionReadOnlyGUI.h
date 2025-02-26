#pragma once
#include <QtWidgets/QWidget>
#include <QPainter>
#include "Prescription.h" 
#include "Observer.h"

class PrescriptionReadOnlyGUI : public QWidget, public Observer {
private:
    Prescription& prescription;  

public:
    PrescriptionReadOnlyGUI(Prescription& prescription) : prescription{ prescription } {
        prescription.addObserver(this);  
        setWindowTitle("PrescriptionReadOnlyGUI");
        resize(400, 400); 
    }

    ~PrescriptionReadOnlyGUI() {
		prescription.removeObserver(this);  
	}   

    void update() override {
        repaint();  
    }

    void paintEvent(QPaintEvent* ev) override {
        QPainter p{ this };  

        int width = this->width();   
        int height = this->height(); 

        int barHeightMax = height - 50;  
        int barWidth = 30;            
        int xPos = width / 2 - barWidth / 2;  
        int yPos = height - 50;         

        int numItems = prescription.getAllPrescription().size();

        int scaledHeight = numItems * barHeightMax / 100;    

        p.setPen(QPen(Qt::black, 2)); 
        p.setBrush(QBrush(Qt::blue)); 
        p.drawRect(xPos, yPos - scaledHeight, barWidth, scaledHeight); 


        p.setPen(QPen(Qt::black, 2)); 
        p.setFont(QFont("Arial", 12)); 
        QString text = QString("Number of meds: %1").arg(numItems);
        p.drawText(xPos - 20, yPos + 15, text);  
    }
};
