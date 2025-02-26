#pragma once
#include<QAbstractTableModel>
#include<vector>
#include "Med.h"

using namespace std;

class TableModel : public QAbstractTableModel {
	vector<Med> meds;
public:
	TableModel(const vector<Med>& meds) :meds{ meds } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return meds.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return  4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Med m = meds[index.row()];
			if (index.column() == 0)
				return QString::fromStdString(m.getName());
			else if (index.column() == 1)
				return  QString::fromStdString(m.getProducer());
			else if (index.column() == 2)
				return  QString::fromStdString(std::to_string(m.getPrice()));
			else if (index.column() == 3)
				return  QString::fromStdString(m.getSubstance());
		}
		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				switch (section) {
				case 0:
					return QString("Name");
				case 1:
					return QString("Producer");
				case 2:
					return QString("Price");
				case 3:
					return QString("Substance");
				default:
					return QVariant{};
				}
			}
		}
		return QVariant{};
	}

	void setMeds(const vector<Med>& meds) {
		this->meds = meds;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		layoutChanged();
	}
};

