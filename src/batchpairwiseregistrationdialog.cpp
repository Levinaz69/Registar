#include <QtCore/QDebug>

#include "../include/batchpairwiseregistrationdialog.h"

BatchPairwiseRegistrationDialog::BatchPairwiseRegistrationDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    //setFixedHeight(sizeHint().height());
    setMinimumHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());


    QStringList headLabels;
    headLabels << "Pair" << "ICP";
    pairBrowser->setHeaderLabels(headLabels);
}

BatchPairwiseRegistrationDialog::~BatchPairwiseRegistrationDialog()
{
}

QStringList BatchPairwiseRegistrationDialog::getSelectedPairNames()
{
    QStringList pairNameList;

    QList<QTreeWidgetItem*> seletcedItems = pairBrowser->selectedItems();
    QList<QTreeWidgetItem*>::Iterator it = seletcedItems.begin();
    while (it != seletcedItems.end())
    {
        if ( !(*it)->text(0).isEmpty() )
        {
            QString pairName = (*it)->text(0);
            pairNameList << pairName;
        }
        ++it;
    }
    return pairNameList;
}

void BatchPairwiseRegistrationDialog::checkSelectedChecker()
{
    QList<QTreeWidgetItem*> seletcedItems = pairBrowser->selectedItems();
    QList<QTreeWidgetItem*>::Iterator it = seletcedItems.begin();
    while (it != seletcedItems.end())
    {
        if ( (*it)->checkState(1) != Qt::Checked )
        {
            (*it)->setCheckState(1, Qt::Checked);
        }
        ++it;
    }
}

QStringList BatchPairwiseRegistrationDialog::getTabLabelList()
{
    QStringList tab_label_list;
    if (!getPairwiseRegistrationDialog())
        return tab_label_list;

    int tab_count = getPairwiseRegistrationDialog()->tabWidget->count();
    for (int i = 0; i < tab_count; ++i)
    {
        QString tab_label = getPairwiseRegistrationDialog()->tabWidget->tabText(i);
        tab_label_list.append(tab_label);
    }

    return tab_label_list;
}

bool BatchPairwiseRegistrationDialog::changeTab(const QString &pairName)
{
    if (!getPairwiseRegistrationDialog())
    {
        qDebug() << "No pairwise registration dialog!";
        return false;
    }

    //QString pairName = cloudName_target + "<-" + cloudName_source;

//    QWidget *current = getPairwiseRegistrationDialog()->tabWidget->currentWidget();
//    if ((current != NULL) && (pairName == current->objectName()))
//        return false;

    QWidget *toBeCurrent = getPairwiseRegistrationDialog()->tabWidget->findChild<QWidget*>(pairName);
    if (toBeCurrent != NULL)
    {
        getPairwiseRegistrationDialog()->tabWidget->setCurrentWidget(toBeCurrent);
        return true;
    }
    return false;
}

void BatchPairwiseRegistrationDialog::addPair(QString pair_label)
{
    QStringList strings;
    strings << pair_label << "icp_finish";
    QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem(strings);
    treeWidgetItem->setCheckState(1, Qt::Unchecked);
    pairBrowser->addTopLevelItem(treeWidgetItem);
    pairBrowser->resizeColumnToContents(0);
    //pairBrowser->resizeColumnToContents(1);
}

void BatchPairwiseRegistrationDialog::on_getPairPushButton_clicked()
{
    if (!getPairwiseRegistrationDialog())
    {
        qDebug() << "No pairwise registration dialog!";
        return;
    }

    pairBrowser->clear();

    QStringList tab_label_list = getTabLabelList();
    QStringList::Iterator it = tab_label_list.begin();
    while (it != tab_label_list.end())
    {
        QString tab_label = *it;

        addPair(tab_label);

        ++it;
    }

}

void BatchPairwiseRegistrationDialog::on_initializePushButton_clicked()
{
    if (!getPairwiseRegistrationDialog())
    {
        qDebug() << "No pairwise registration dialog!";
        return;
    }

    QString text = initializePairText->toPlainText();
    QStringList lines = text.split("\n");

    int nPair = 0;
    for (int i = 0; i < lines.size(); ++i)
    {
        if (lines[i] != "")
        {
            QStringList cloudList = lines[i].split("<-");

            for (int j = 1; j < cloudList.size(); ++j)
            {
                QString cloudName_target = cloudList[j-1];
                QString cloudName_source = cloudList[j];

                int targetIdx = getPairwiseRegistrationDialog()->targetComboBox->findText(cloudName_target, Qt::MatchExactly);
                int sourceIdx = getPairwiseRegistrationDialog()->sourceComboBox->findText(cloudName_source, Qt::MatchExactly);
                if (targetIdx == -1 || sourceIdx == -1)
                {
                    qDebug() << "Cannot find given cloud" << cloudName_target << "<-" << cloudName_source << "!";
                    continue;
                }

                getPairwiseRegistrationDialog()->targetComboBox->setCurrentIndex(targetIdx);
                getPairwiseRegistrationDialog()->sourceComboBox->setCurrentIndex(sourceIdx);

                QString pairName = cloudName_target + "<-" + cloudName_source;
                QWidget *current = getPairwiseRegistrationDialog()->tabWidget->currentWidget();
                if ((current != NULL) && (pairName == current->objectName()))
                {
                    qDebug() << cloudName_target << "<-" << cloudName_source << "already exists!";
                    continue;
                }

                getPairwiseRegistrationDialog()->on_initializePushButton_clicked();
                qDebug() << "pair" << pairName << "initialized!";

                addPair(pairName);
                ++nPair;
            }

        }
    }

    QMessageBox::information(this, "initialize finished", QString("initialize for ") + QString::number(nPair) + QString(" pairs finished!"), QMessageBox::Ok);

}


void BatchPairwiseRegistrationDialog::on_icpPushButton_clicked()
{
    if (!getPairwiseRegistrationDialog())
    {
        qDebug() << "No pairwise registration dialog!";
        return;
    }

    QList<double> distThresholdList;
    if (distThresholdListChecker->checkState() == Qt::Checked)
    {
        QDoubleValidator distThresholdValidator;
        distThresholdValidator.setBottom(getPairwiseRegistrationDialog()->distanceDoubleSpinBox->minimum());
        distThresholdValidator.setTop(getPairwiseRegistrationDialog()->distanceDoubleSpinBox->maximum());
        distThresholdValidator.setDecimals(getPairwiseRegistrationDialog()->distanceDoubleSpinBox->decimals());
        distThresholdValidator.setNotation(QDoubleValidator::StandardNotation);

        QString dText = distThresholdText->toPlainText();
        QStringList dLines = dText.split("\n");
        int validate_pos = 0;
        for (int i = 0; i < dLines.size(); ++i)
        {
            if (distThresholdValidator.validate(dLines[i], validate_pos) == QValidator::Acceptable)
            {
                distThresholdList.append(dLines[i].toDouble());
            }
        }
        if (distThresholdList.empty())
        {
            qDebug() << "Invalid distance threshold list!";
            return;
        }
        else
        {
            qDebug() << "Accept distance threshold list:";
            for (int i = 0; i < distThresholdList.size(); ++i)
                qDebug() << " " << distThresholdList[i];
        }
    }

    QStringList tab_label_list = getTabLabelList();
    QStringList pairNameList = getSelectedPairNames();

    QStringList::Iterator pair_it = pairNameList.begin();
    while (pair_it != pairNameList.end())
    {

        if (changeTab(*pair_it))
        {
            if (distThresholdListChecker->checkState() == Qt::Checked)
            {
                for (int i = 0; i < distThresholdList.size(); ++i)
                {
                    getPairwiseRegistrationDialog()->distanceDoubleSpinBox->setValue(distThresholdList[i]);
                    getPairwiseRegistrationDialog()->on_icpPushButton_clicked();
                    qDebug() << *pair_it << " ICP with distance threshold:" << distThresholdList[i];
                }
            }
            else
            {
                getPairwiseRegistrationDialog()->on_icpPushButton_clicked();
                qDebug() << *pair_it << " ICP!";
            }

        }
        ++pair_it;
    }

    checkSelectedChecker();
    QMessageBox::information(this, "ICP finished", QString("ICP for ") + QString::number(pairNameList.size()) + QString(" pairs finished!"), QMessageBox::Ok);

}

void BatchPairwiseRegistrationDialog::on_distThresholdListChecker_stateChanged()
{
    if (distThresholdListChecker->checkState() == Qt::Checked)
        distThresholdText->setEnabled(true);
    else
        distThresholdText->setEnabled(false);
}


