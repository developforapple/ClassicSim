#include "i18n.h"

#include <Winnls.h>
#pragma comment(lib,"Kernel32.lib")

I18N::I18N() {
    LANGID lid = GetSystemDefaultLangID();
    // 0X0804 Chinese (Simplified)
    // 0X0404 Chinese (Traditional)
    if (lid == 0X0804 || lid == 0X0404) {
        lang = "zh";
    } else {
        lang = "en";
    }
}

I18N::~I18N() {

}

I18N& I18N::get_instance() {
    static I18N instance;
    return instance;
}
