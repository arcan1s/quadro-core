/***************************************************************************
 *   This file is part of quadro                                           *
 *                                                                         *
 *   quadro is free software: you can redistribute it and/or               *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   quadro is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with quadro. If not, see http://www.gnu.org/licenses/           *
 ***************************************************************************/


#include "editappwindow.h"
#include "ui_editappwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QListWidget>
#include <QStandardPaths>


EditAppWindow::EditAppWindow(QWidget *parent, ApplicationItem *item)
    : QDialog(parent),
      m_item(item)
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    ui = new Ui::EditAppWindow;
    ui->setupUi(this);

    connect(ui->lineEdit_icon, SIGNAL(textEdited(const QString)), this,
            SLOT(updateIcon(const QString)));
    connect(ui->pushButton_categories, SIGNAL(clicked(const bool)), this,
            SLOT(addCategory()));
    connect(ui->pushButton_exec, SIGNAL(clicked(const bool)), this,
            SLOT(selectExec()));
    connect(ui->pushButton_path, SIGNAL(clicked(const bool)), this,
            SLOT(selectPath()));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(this, SIGNAL(accepted()), this, SLOT(saveDesktop()));
}


EditAppWindow::~EditAppWindow()
{
    qCDebug(LOG_UI) << __PRETTY_FUNCTION__;

    delete ui;
}


void EditAppWindow::saveDesktop()
{
    m_item->setName(ui->lineEdit_name->text());
    m_item->setGenericName(ui->lineEdit_description->text());
    m_item->setComment(ui->lineEdit_comment->text());
    m_item->setIcon(ui->lineEdit_icon->text());
    m_item->setExec(ui->lineEdit_exec->text());
    m_item->setCategories(ui->lineEdit_categories->text().split(QChar(';')));
    m_item->setPath(ui->lineEdit_path->text());
    m_item->setNoDisplay(ui->checkBox_noDisplay->isChecked());
    m_item->setTerminal(ui->checkBox_terminal->isChecked());

    m_item->saveDesktop(QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation));
}


void EditAppWindow::showWindow()
{
    // set values
    ui->lineEdit_name->setText(m_item->name());
    ui->lineEdit_description->setText(m_item->genericName());
    ui->lineEdit_comment->setText(m_item->comment());
    ui->lineEdit_icon->setText(m_item->icon());
    // 25 is a magic number comes from label size
    ui->label_iconPreview->setPixmap(m_item->appIcon().pixmap(25, 25));
    ui->lineEdit_exec->setText(m_item->exec());
    ui->lineEdit_categories->setText(m_item->categories().join(QChar(';')));
    ui->lineEdit_path->setText(m_item->path());
    ui->checkBox_noDisplay->setChecked(m_item->noDisplay());
    ui->checkBox_terminal->setChecked(m_item->terminal());

    open();
}


void EditAppWindow::selectExec()
{
    QString selection = QFileDialog::getOpenFileName(this, QApplication::translate("EditAppWindow", "Executable"));
    qCInfo(LOG_UI) << "Select file" << selection;

    if (!selection.isEmpty())
        ui->lineEdit_exec->setText(selection);
}


void EditAppWindow::addCategory()
{
    // init ui
    QDialog *categoryDialog = new QDialog(this);
    categoryDialog->setWindowTitle(QApplication::translate("EditAppWindow", "Categories"));
    QListWidget *listWidget = new QListWidget(categoryDialog);
    QDialogButtonBox *dialogButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, categoryDialog);
    QVBoxLayout *layout = new QVBoxLayout(categoryDialog);
    layout->addWidget(listWidget);
    layout->addWidget(dialogButtons);
    categoryDialog->setLayout(layout);

    // fill widget
    listWidget->addItems(LauncherCore::availableCategories());
    connect(dialogButtons, SIGNAL(accepted()), categoryDialog, SLOT(accept()));
    connect(dialogButtons, SIGNAL(rejected()), categoryDialog, SLOT(reject()));

    // exec
    QStringList categories = ui->lineEdit_categories->text().split(QChar(';'));
    switch (categoryDialog->exec()) {
    case QDialog::Accepted:
        categories.append(listWidget->currentItem()->text());
        ui->lineEdit_categories->setText(categories.join(QChar(';')));
        break;
    case QDialog::Rejected:
    default:
        break;
    }

    delete categoryDialog;
}


void EditAppWindow::selectPath()
{
    QString selection = QFileDialog::getExistingDirectory(this, QApplication::translate("EditAppWindow", "Working directory"));
    qCInfo(LOG_UI) << "Select file" << selection;

    if (!selection.isEmpty())
        ui->lineEdit_path->setText(selection);
}


void EditAppWindow::updateIcon(const QString text)
{
    qCDebug(LOG_UI) << "Current icon name" << text;

    ui->label_iconPreview->setPixmap(QIcon::fromTheme(text).pixmap(25, 25));
}
