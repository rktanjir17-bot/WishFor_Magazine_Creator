#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Page.h"
#include <string>
#include <vector>

class Magazine {
private:
    std::string title;
    std::string occasion;
    std::string authorName;
    std::vector<Page> pages;

public:
    Magazine(const std::string& magTitle, const std::string& magOccasion, const std::string& author)
        : title(magTitle), occasion(magOccasion), authorName(author) {}

    void addPage(const Page& page) {
        pages.push_back(page);
    }

    std::string getTitle() const { return title; }
    std::string getOccasion() const { return occasion; }
    std::string getAuthor() const { return authorName; }
    const std::vector<Page>& getPages() const { return pages; }
};

#endif // MAGAZINE_H