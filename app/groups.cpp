#include "groups.h"
#include "ui_groups.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>

Groups::Groups(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Groups)
{
    ui->setupUi(this);

    connect(ui->btnConnect_1,SIGNAL(clicked(bool)),this, SLOT(dbconnect()));
    connect(ui->btnSelectAll_1,SIGNAL(clicked(bool)),this, SLOT(selectAll()));
    connect(ui->btnAdd_1,SIGNAL(clicked(bool)),this, SLOT(add()));
    connect(ui->btnDel_1,SIGNAL(clicked(bool)),this, SLOT(del()));

    // Количество столбцов
    ui->twGroups->setColumnCount(5);
    // Возможность прокрутки
    ui->twGroups->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twGroups->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twGroups->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
    ui->twGroups->setHorizontalHeaderItem(0,new QTableWidgetItem("Название"));
    ui->twGroups->setHorizontalHeaderItem(1,new QTableWidgetItem("Дата"));
    ui->twGroups->setHorizontalHeaderItem(2,new QTableWidgetItem("Страна"));
    ui->twGroups->setHorizontalHeaderItem(3,new QTableWidgetItem("Кол-во участников"));
    ui->twGroups->setHorizontalHeaderItem(4,new QTableWidgetItem("Жанр"));
    // Последний столбец растягивается при изменении размера формы
    ui->twGroups->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twGroups->setSortingEnabled(true);
    //ui->twGroups->sortByColumn(0);   ЭТА СТРОКА ЛОМАЕТ ВЫВОД ЗАПИСЕЙ
    // Запрет на изменение ячеек таблицы при отображении
    //ui->twGroups->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Groups::~Groups()
{
    if( dbconn.isOpen())
        dbconn.close();
    delete ui;
}



void Groups::dbconnect(){
    if(!dbconn.isOpen()){
        // Если соединение не открыто, то вывести список доступных драйверов БД
        // (вывод в поле teResult, метод append добавляет строки).
        ui->teResult->append("SQL drivers:");
        ui->teResult->append(QSqlDatabase::drivers().join(","));
        // Создать глобальную переменную для установки соединения с БД
        dbconn=QSqlDatabase::addDatabase("QPSQL");
        // Установить параметры соединения: имя БД, адрес хоста, логин и пароль пользователя, порт (если отличается от стандартного)
        dbconn.setDatabaseName("musicbands");
        dbconn.setHostName("localhost");
        dbconn.setUserName("alexey");
        dbconn.setPassword("448944rr");
        // Открыть соединениe и результат вывести в окно вывода
        if( dbconn.open() )
            ui->teResult->append("Соединение установлено...");
        else{
            ui->teResult->append("Ошибка соединения:");
            ui->teResult->append(dbconn.lastError().text());
        }
    }
    else
    // Если соединение уже открыто, то сообщить об этом
    ui->teResult->append("Соединение уже установлено...");
}






void Groups::selectAll(){
    // Очистить содержимое компонента
    ui->twGroups->clearContents();
    // Если соединение не открыто, то вызвать нашу функцию для открытия
    // если подключиться не удалось, то вывести сообщение об ошибке и
    // выйти из функции
    if( !dbconn.isOpen() )
    {
        dbconnect();
        if( !dbconn.isOpen() )
        {
            QMessageBox::critical(this,"Error",dbconn.lastError().text());
            return;
        }
    }
    // Создать объект запроса с привязкой к установленному соединению
    QSqlQuery query(dbconn);
    // Создать строку запроса на выборку данных
    QString sqlstr = "select * from bands";
    // Выполнить запрос и поверить его успешность
    if( !query.exec(sqlstr) )
    {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }
    // Если запрос активен (успешно завершен),
    // то вывести сообщение о прочитанном количестве строк в окно вывода
    // и установить количество строк для компонента таблицы
    if( query.isActive())
    ui->twGroups->setRowCount( query.size());
    else
    ui->twGroups->setRowCount( 0);
    ui->teResult->append( QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next())
    {
        ui->twGroups->setItem(i,0,new
        QTableWidgetItem(query.value("band_name").toString()));
        ui->twGroups->setItem(i,1,new
        QTableWidgetItem(query.value("creation_date").toString()));
        ui->twGroups->setItem(i,2,new
        QTableWidgetItem(query.value("country").toString()));
        ui->twGroups->setItem(i,3,new
        QTableWidgetItem(query.value("members_amount").toString()));
        ui->twGroups->setItem(i,4,new
        QTableWidgetItem(query.value("genre").toString()));
        i++;
    }
}





void Groups::add()
{
    // Подключиться к БД
    if( !dbconn.isOpen() )
    {
        dbconnect();
        if( !dbconn.isOpen() )
        {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
        }
    }
    QSqlQuery query(dbconn);
    // Создать строку запроса
    QString sqlstr = "insert into bands (band_name, creation_date, country, members_amount, genre) values (?,?,?,?,?)";

    // Подготовить запрос
    query.prepare(sqlstr);
    // Передать параметры из полей ввода в запрос
    query.bindValue(0,ui->leBandName->text());
    query.bindValue(1,ui->leCreationDate->text());
    query.bindValue(2,ui->leBandCountry->text());
    // Если тип поля отличается от строкового, то преобразовать его
    query.bindValue(3,ui->leMembersAmount->text().toInt());
    query.bindValue(4,ui->leGenre->text());
    // Выполнить запрос
    if( !query.exec() )
    {
        ui->teResult->append( query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }
    // Если запрос выполнен, то вывести сообщение одобавлении строки
    ui->teResult->append( QString("AddRead %1 rows").arg(query.numRowsAffected()) );
    // и обновить записи в компоненте таблицы
    selectAll();
}






void Groups::del(){
// Подключение к БД
    if( !dbconn.isOpen() )
    {
        dbconnect();
        if( !dbconn.isOpen() )
        {
            QMessageBox::critical(this,"Error",dbconn.lastError().text());
            return;
        }
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twGroups->currentRow();
    // Если он меньше 0 (строка не выбрана), то
    // сообщение об ошибке и выход из функции
    if( currow < 0 )
    {
        QMessageBox::critical(this,"Ошибка","Не выбрана строка!");
        return;
    }
    // Спросить у пользователя подтверждение удаления записи
    // Используется статический метод QMessageBox::question
    // для задания вопроса, который возвращает код нажатой кнопки
    if( QMessageBox::question(this,"Удалить","Удалить запись?",
    QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Cancel)
    return;
    // Создать объект запроса
    QSqlQuery query(dbconn);
    // Создать строку запроса.
    // Вместо подготовки запроса и передачи параметров значение параметра
    // конкатенируется со строкой запроса
    // Обратите,что строковое значение помещается в одинарные кавычки
    // Значение выбирается из компонента таблицы методом item(row,col)
    QString sqlstr = "delete from bands where band_name = '"
    + ui->twGroups->item(currow,0)->text() + "'";
    // Выполнить строку запроса и проверить его успешность
    if( !query.exec(sqlstr) )
    {
        ui->teResult->append( query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }
    // Вывести сообщение об удалении строки
    ui->teResult->append( QString("Del %1 rows").arg(query.numRowsAffected()) );
    // Обновить содержимое компонента таблицы
    selectAll();
}

