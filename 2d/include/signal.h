#ifndef Signal_H
#define Signal_H
#include <QVector>
#include <QDebug>

template<typename T>
class Signal{
public:
    Signal(Signal* parent,QString name,QVector<T> time,QVector<T> rate):parent(parent),name(name){
        data.first=time;
        data.second=rate;
        if(parent!=nullptr)parent->childs.push_back(this);
    }
    bool push_data(QString n,T*t,T*r){
        for(Signal* signal : childs){
            if(signal->name==n){
                signal->data.first.push_back(*t);
                signal->data.second.push_back(*r);
                return true;
            }
        }
        return false;
    }
    std::pair<QVector<T>,QVector<T>>* read_data(const QString& name,const QString& parent){
        for(Signal* signal : childs){
            if(signal->name==parent){
                for(Signal* sig_child: signal->childs)
                    if(sig_child->name==name)return &sig_child->data;
            }
        }
        return nullptr;
    }
    QVector<Signal*> childs;
    Signal* parent=nullptr;
private:
    std::pair<QVector<T>,QVector<T>> data;
    QString name;
};

#endif // Signal_H
