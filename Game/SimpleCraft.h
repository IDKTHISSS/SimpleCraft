//
// Created by IDKTHIS on 25.02.2025.
//

#ifndef SIMPLECRAFT_H
#define SIMPLECRAFT_H
#include <memory>

#include "Engine/Application.h"


class SimpleCraft : public Core::BaseApplication{

public:
    static std::shared_ptr<SimpleCraft> Get() {
        static std::shared_ptr<SimpleCraft> _instance = std::make_shared<SimpleCraft>();
        return _instance;
    }

};



#endif //SIMPLECRAFT_H
