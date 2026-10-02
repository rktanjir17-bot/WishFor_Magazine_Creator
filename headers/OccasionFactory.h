#ifndef OCCASION_FACTORY_H
#define OCCASION_FACTORY_H

#include "Magazine.h"
#include "TextBlock.h"
#include "ImageBlock.h"
#include <memory>

class OccasionFactory {
public:
    static std::unique_ptr<Magazine> createMagazineTemplate(const std::string& occasion, const std::string& author, const std::string& userMsg, const std::string& imgUrl) {
        auto mag = std::make_unique<Magazine>("VOGUE : Special Edition", occasion, author);

        Page coverPage(1);
        coverPage.addBlock(std::make_shared<ImageBlock>("img1", imgUrl, "Cover Photo"));
        coverPage.addBlock(std::make_shared<TextBlock>("title1", mag->getTitle(), "magazine-heading"));
        coverPage.addBlock(std::make_shared<TextBlock>("sub1", "A Special " + occasion + " Memory", "magazine-subhead"));
        coverPage.addBlock(std::make_shared<TextBlock>("msg1", "\"" + userMsg + "\"", "quote-text"));
        coverPage.addBlock(std::make_shared<TextBlock>("author1", "— " + author, "quote-author"));

        mag->addPage(coverPage);
        return mag;
    }
};

#endif // OCCASION_FACTORY_H