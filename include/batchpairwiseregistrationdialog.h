#ifndef BATCHPAIRWISEREGISTRATIONDIALOG_H
#define BATCHPAIRWISEREGISTRATIONDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QProgressDialog>
#include "pairwiseregistrationdialog.h"

#include "ui_BatchPairwiseRegistrationDialog.h"


class BatchPairwiseRegistrationDialog : public QDialog, public Ui_BatchPairwiseRegistrationDialog
{
    Q_OBJECT

public:
    BatchPairwiseRegistrationDialog(QWidget *parent = 0);
    virtual ~BatchPairwiseRegistrationDialog();

    PairwiseRegistrationDialog* getPairwiseRegistrationDialog() { return *pairwiseRegistrationDialogPtr; }

private:
    QStringList getSelectedPairNames();
    QStringList getTabLabelList();
    bool changeTab(const QString &pairName);
    void addPair(QString pair_label);

private slots:
        void on_getPairPushButton_clicked();
        void on_initializePushButton_clicked();
        void on_icpPushButton_clicked();
        void on_distThresholdListChecker_stateChanged();

public:
    PairwiseRegistrationDialog** pairwiseRegistrationDialogPtr;

};

#endif // BATCHPAIRWISEREGISTRATIONDIALOG_H
