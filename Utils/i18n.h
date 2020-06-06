#ifndef I18N_H
#define I18N_H

#include <QObject>
#include <QApplication>

class I18N
{
public:
    static I18N& get_instance();
    QString lang;

    void init(QApplication&);
private:
    I18N();
    ~I18N();
};

#define L_LANG (I18N::get_instance().lang)

#endif // I18N_H
