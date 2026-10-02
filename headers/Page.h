#ifndef PAGE_H
#define PAGE_H

#include "ContentBlock.h"
#include <vector>
#include <memory>
#include <Wt/WContainerWidget.h>

// Page class encapsulating a collection of ContentBlocks (Composition)
class Page {
private:
    int pageNumber;
    std::vector<std::shared_ptr<ContentBlock>> blocks;

public:
    Page(int number) : pageNumber(number) {}

    void addBlock(std::shared_ptr<ContentBlock> block) {
        blocks.push_back(block);
    }

    void render(Wt::WContainerWidget* parent) {
        auto pageContainer = parent->addWidget(std::make_unique<Wt::WContainerWidget>());
        pageContainer->setStyleClass("magazine-page");

        for (const auto& block : blocks) {
            block->render(pageContainer);
        }
    }

    int getPageNumber() const { return pageNumber; }
};

#endif // PAGE_H