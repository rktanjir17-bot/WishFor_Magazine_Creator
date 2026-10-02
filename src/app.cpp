#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>
#include "../headers/OccasionFactory.h"
#include "../headers/JsonStore.h"
#include <fstream>
#include <cstdlib>
#include <memory>
#include <string>

class WishForApp : public Wt::WApplication {
public:
    WishForApp(const Wt::WEnvironment& env) : Wt::WApplication(env) {
        setTitle("WishFor - Custom Magazine Creator");
        useStyleSheet("wwwroot/style.css");

        auto container = root();

        // 1. Hero Title Section
        auto hero = container->addWidget(std::make_unique<Wt::WContainerWidget>());
        hero->setStyleClass("hero-section");
        
        auto title = hero->addWidget(std::make_unique<Wt::WText>("<h1>Celebrate & Capture Memories</h1>"));
        title->setTextFormat(Wt::TextFormat::XHTML);

        // 2. Dynamic Input Form Section
        auto formBox = container->addWidget(std::make_unique<Wt::WContainerWidget>());
        formBox->setStyleClass("wish-form-box");

        formBox->addWidget(std::make_unique<Wt::WText>("<label>Your Name / Author:</label>"));
        auto nameInput = formBox->addWidget(std::make_unique<Wt::WLineEdit>());
        nameInput->setPlaceholderText("e.g. Tanjir");

        formBox->addWidget(std::make_unique<Wt::WText>("<label>Picture URL:</label>"));
        auto imgInput = formBox->addWidget(std::make_unique<Wt::WLineEdit>());
        imgInput->setPlaceholderText("Paste image link");

        formBox->addWidget(std::make_unique<Wt::WText>("<label>Your Wish Message:</label>"));
        auto msgInput = formBox->addWidget(std::make_unique<Wt::WTextArea>());
        msgInput->setPlaceholderText("Write your special wish here...");
        msgInput->setRows(3);

        auto btnContainer = formBox->addWidget(std::make_unique<Wt::WContainerWidget>());
        btnContainer->setStyleClass("action-bar");

        auto addBtn = btnContainer->addWidget(std::make_unique<Wt::WPushButton>("✨ Update Preview"));
        addBtn->setStyleClass("btn-primary");

        // 3. Live Preview
        auto magazineView = container->addWidget(std::make_unique<Wt::WContainerWidget>());
        magazineView->setStyleClass("magazine-viewport");

        auto renderApp = [=]() {
            std::string author = nameInput->text().empty() ? "Tanjir" : nameInput->text().toUTF8();
            std::string msg = msgInput->text().empty() ? "Special Moments Captured" : msgInput->text().toUTF8();
            std::string img = imgInput->text().empty() ? "https://images.unsplash.com/photo-1534528741775-53994a69daeb" : imgInput->text().toUTF8();

            auto mag = OccasionFactory::createMagazineTemplate("Birthday", author, msg, img);
            JsonStore::saveMagazine("mag_001", author, msg, img);

            magazineView->clear();
            for (const auto& page : mag->getPages()) {
                const_cast<Page&>(page).render(magazineView);
            }
        };

        renderApp();
        addBtn->clicked().connect(renderApp);
    }
};

int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<WishForApp>(env);
    });
}