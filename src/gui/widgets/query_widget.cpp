#include "gui/widgets/query_widget.h"

#include <QHBoxLayout>
#include <QSplitter>

#include "shell/shell_widget.h"
#include "gui/widgets/output_widget.h"

namespace fastoredis
{
    QueryWidget::QueryWidget(IServerPtr server, QWidget* parent)
        : QWidget(parent)
    {
        shellWidget_ = new ShellWidget(server);
        outputWidget_ = new OutputWidget;
        VERIFY(connect(shellWidget_, SIGNAL(rootCreated(const EventsInfo::CommandRootCreatedInfo&)), outputWidget_, SLOT(rootCreate(const EventsInfo::CommandRootCreatedInfo&))));
        VERIFY(connect(shellWidget_, SIGNAL(rootCompleated(const EventsInfo::CommandRootCompleatedInfo& )), outputWidget_, SLOT(rootCompleate(const EventsInfo::CommandRootCompleatedInfo&))));
        VERIFY(connect(shellWidget_, SIGNAL(addedChild(FastoObject *)), outputWidget_, SLOT(addChild(FastoObject *))));

        QSplitter *splitter = new QSplitter;
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(1);
        splitter->setContentsMargins(0, 0, 0, 0);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        splitter->addWidget(shellWidget_);
        splitter->addWidget(outputWidget_);
        mainLayout->addWidget(splitter);

        setLayout(mainLayout);
    }

    QString QueryWidget::inputText() const
    {
        return shellWidget_->text();
    }

    void QueryWidget::reload()
    {

    }

    QueryWidget* QueryWidget::clone(const QString &text)
    {
        QueryWidget *result = new QueryWidget(shellWidget_->server(), parentWidget());
        result->shellWidget_->setText(text);
        return result;
    }
}
