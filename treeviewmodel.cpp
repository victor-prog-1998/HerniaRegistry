#include "treeviewmodel.h"
#include "dbworker.h"
#include <QDebug>

TreeViewModel::TreeViewModel(QObject *parent) : QObject(parent)
{


}

QList<QObject *> TreeViewModel::data()
{
    return m_data;
}

void TreeViewModel::log()
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        TreeElement *tmp = qobject_cast<TreeElement*>(m_data[i]);
        QString str = "[" + tmp->text() + ", " + QString::number(i) + "], level: " + QString::number(tmp->level()) +
                ", visible: " + QString::number((int)tmp->visible()) +
                ", open: " + QString::number((int)tmp->open()) + ", checked: " + QString::number((int)tmp->checked());
        qDebug() << str;
    }
}

void TreeViewModel::reset()
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        TreeElement *tmp = qobject_cast<TreeElement*>(m_data[i]);
        tmp->reset();
    }
}

void TreeViewModel::initModel(DBWorker &dbWorker)
{
    /* Правила добавления элементов в дерево:
     * 1. Для верхних элементов в качестве предка указывается сама модель (this)
     * 2. Для остальных - указатель на другой элемент, в который они вложены
     * 3. Уровни вложенности, видимость, разворачиваемость вычисляются автоматически в классе TreeElement
     * 4. При добавлении созданных элементов в список (m_data) нужно добавлять их в том порядке,
     *    в каком они будут следовать друг за другом в полностью развернутом дереве
     *    (с учетом разворачиваемых элементов)
    */

     // ********************************** Раздел "Пол" ******************************************
     QObject *sex = new TreeElement("Пол", this);
        QObject *male = new TreeElement("Мужской", sex);
        QObject *female = new TreeElement("Женский", sex);

        // ********************************** Раздел "Регион" ******************************************
     QObject *region = new TreeElement("Регион", this);
     QList<QObject*> regionsList;
     for(auto reg: dbWorker.regions())
         regionsList.push_back(new TreeElement(reg, region));

     // ********************************** Раздел "Факторы риска" ************************************
     QObject *riskFactors = new TreeElement("Факторы риска", this);
     QObject *occupation = new TreeElement("Род деятельности", riskFactors);
     QList<QObject*> occupationsList;
     for(auto occ: dbWorker.occupations())
         occupationsList.push_back(new TreeElement(occ, occupation));
     QObject *sportActivity = new TreeElement("Занятия спортом", riskFactors);
     QList<QObject*> sportActivitiesList;
     for(auto sport: dbWorker.sportActivities())
         sportActivitiesList.push_back(new TreeElement(sport, sportActivity));
     QObject *smokingHistory = new TreeElement("Курение", riskFactors);
     QList<QObject*> smokingHistoriesList;
     for(auto smoking: dbWorker.smokingHistories())
         smokingHistoriesList.push_back(new TreeElement(smoking, smokingHistory));
     QObject *otherFactors = new TreeElement("Другие факторы", riskFactors);
     QStringList otherFactorsStringList = {"Сахарный диабет I типа", "Сахарный диабет II типа",
                                           "ХОБЛ", "Гипертония", "Сердечное заболевание",
                                           "Заболевание почек", "Гастрит",  "Пептическая язва",
                                           "Аневризмы аорты", "Иммуносупрессия", "Коагулопатия",
                                           "Ингибиторы агрегации тромбоцитов"};
     QList<QObject*> otherFactorsList;
     for(auto oth: otherFactorsStringList)
         otherFactorsList.push_back(new TreeElement(oth, otherFactors));


     // ********************************** Раздел "Грыжа" ******************************************
     QObject *hernia = new TreeElement("Грыжа", this);

     // Послеоперационная вентральная грыжа
     QObject *ventralHernia = new TreeElement("Послеоперационная вентральная", hernia);

     QObject *ventralMidlineHernia = new TreeElement("Срединная", ventralHernia);
     QList<QObject*> ventralMidlineHerniaTypesList;
     for(auto type: dbWorker.ventralMidlineHerniaTypes())
         ventralMidlineHerniaTypesList.push_back(new TreeElement(type, ventralMidlineHernia));

     QObject *ventralLateralHernia = new TreeElement("Латеральная", ventralHernia);
     QList<QObject*> ventralLateralHerniaTypesList;
     for(auto type: dbWorker.ventralLateralHerniaTypes())
         ventralLateralHerniaTypesList.push_back(new TreeElement(type, ventralLateralHernia));
     // \Послеоперационная вентральная грыжа

     // Паховая грыжа
     QObject *groinHernia = new TreeElement("Паховая", hernia);
     QList<QObject*> groinHerniaTypesList;
     for(auto type: dbWorker.groinHerniaTypes())
         groinHerniaTypesList.push_back(new TreeElement(type, groinHernia));
     // \Паховая грыжа
     // Сторона
     QObject *herniaSide = new TreeElement("Сторона", hernia);
     QList<QObject*> herniaSideList;
     for(auto side: dbWorker.sides())
         herniaSideList.push_back(new TreeElement(side, herniaSide));
     // \ Сторона
     // Рецидив
     QObject* recurrence = new TreeElement("Рецидив", hernia);
     // \ Рецидив
     // \Грыжа

     // ********************************** Раздел "Операции" ******************************************

     QObject *operations = new TreeElement("Операции", this);
     QObject *tensionMethod = new TreeElement("Натяжной способ", operations);

     QObject *tensionTechnique = new TreeElement("Техника натяжного способа", tensionMethod);

     QList<QObject*> tensionTechniquesList;
     for(auto tech: dbWorker.tissueRepairTechniques())
         tensionTechniquesList.push_back(new TreeElement(tech, tensionTechnique));


     // все, что относится к ненатяжному способу
     QObject *nonTensionMethod = new TreeElement("Ненатяжной способ", operations);

     QObject *nonTensionTechnique = new TreeElement("Техника ненатяжного способа", nonTensionMethod);
     QList<QObject*> nonTensionTechniquesList;
     for(auto tech: dbWorker.meshImplantRepairTechniques())
         nonTensionTechniquesList.push_back(new TreeElement(tech, nonTensionTechnique));

     QObject *meshType = new TreeElement("Тип сетки", nonTensionMethod);
     QList<QObject*> meshesList;
     for(auto mesh: dbWorker.meshes())
        meshesList.push_back(new TreeElement(mesh, meshType));

     QObject *fixationType = new TreeElement("Тип фиксации", nonTensionMethod);
     QList<QObject*> fixationsList;
     fixationsList.push_back(new TreeElement("Сетка не фиксировалась", fixationType));
     for(auto fix: dbWorker.fixationTypes())
         fixationsList.push_back(new TreeElement(fix, fixationType));

     QObject *tuckersType = new TreeElement("Тип такеров", nonTensionMethod);
     QList<QObject*> tuckersList;
     for(auto tucker: dbWorker.tuckers())
         tuckersList.push_back(new TreeElement(tucker, tuckersType));
     // ----------------------------------------------------

     QObject *complications = new TreeElement("Осложнения", operations);

     QList<QObject*> complicationsList;
     complicationsList.push_back(new TreeElement("Интраоперационные", complications));
     complicationsList.push_back(new TreeElement("Ранние послеоперационные", complications));
     complicationsList.push_back(new TreeElement("Поздние послеоперационные", complications));









     // **************** Добавление в список m_data *******************************************

     // метод push_back - для единичных элементов, append - для списков

     this->m_data.push_back(sex);
        this->m_data.push_back(male);
        this->m_data.push_back(female);
     this->m_data.push_back(region);
        this->m_data.append(regionsList);
     this->m_data.push_back(riskFactors);
        this->m_data.push_back(occupation);
            this->m_data.append(occupationsList);
        this->m_data.push_back(sportActivity);
            this->m_data.append(sportActivitiesList);
        this->m_data.push_back(smokingHistory);
            this->m_data.append(smokingHistoriesList);
        this->m_data.push_back(otherFactors);
            this->m_data.append(otherFactorsList);


     this->m_data.push_back(hernia);
        this->m_data.push_back(ventralHernia);
            this->m_data.push_back(ventralMidlineHernia);
                this->m_data.append(ventralMidlineHerniaTypesList);
            this->m_data.push_back(ventralLateralHernia);
                this->m_data.append(ventralLateralHerniaTypesList);
        this->m_data.push_back(groinHernia);
            this->m_data.append(groinHerniaTypesList);
        this->m_data.push_back(herniaSide);
            this->m_data.append(herniaSideList);
        this->m_data.push_back(recurrence);

     this->m_data.push_back(operations);
     this->m_data.push_back(tensionMethod);
     this->m_data.push_back(tensionTechnique);
     this->m_data.append(tensionTechniquesList);
     this->m_data.push_back(nonTensionMethod);
     this->m_data.push_back(nonTensionTechnique);
     this->m_data.append(nonTensionTechniquesList);
     this->m_data.push_back(meshType);
     this->m_data.append(meshesList);
     this->m_data.push_back(fixationType);
     this->m_data.append(fixationsList);
     this->m_data.push_back(tuckersType);
     this->m_data.append(tuckersList);

     this->m_data.push_back(complications);
     this->m_data.append(complicationsList);



}

TreeElement *TreeViewModel::getTreeElement(const QString &text)
{
    QList<TreeElement*> treeElementList;
    for(auto d: this->m_data)
        treeElementList.push_back(qobject_cast<TreeElement*>(d));
    //auto el = std::find(treeElementList.begin(), treeElementList.end(), text);

    auto el = std::find(treeElementList.begin(), treeElementList.end(), text);
    if(el == treeElementList.end())
        return nullptr;
    return *el;
}

bool TreeViewModel::childrenAreChecked(const QString &parentElement)
{
    TreeElement *p = this->getTreeElement(parentElement);
    for(auto ch: p->children())
        if(qobject_cast<TreeElement*>(ch)->checked())
            return true;
    return false;
}

bool TreeViewModel::allChildrenAreChecked(const QString &parentElement)
{
    TreeElement *p = this->getTreeElement(parentElement);
    for(auto ch: p->children())
        if(!qobject_cast<TreeElement*>(ch)->checked())
            return false;
    return true;
}

QStringList TreeViewModel::getCheckedChildren(const QString &parentElement)
{
    TreeElement *p = this->getTreeElement(parentElement);
    QStringList checkedChildren;
    for(auto ch: p->children())
    {
        TreeElement *child = qobject_cast<TreeElement*>(ch);
        if(child->checked())
            checkedChildren.push_back(child->text());
    }
    return checkedChildren;
}

bool TreeViewModel::elementIsChecked(const QString &element)
{
    return this->getTreeElement(element)->isChecked();
}



