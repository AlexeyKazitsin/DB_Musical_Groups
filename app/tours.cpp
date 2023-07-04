#include "tours.h"
#include "ui_tours.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>

Tours::Tours(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tours)
{
    ui->setupUi(this);

    connect(ui->btnConnect_1,SIGNAL(clicked(bool)),this, SLOT(dbconnect()));
    connect(ui->btnSelectAll_1,SIGNAL(clicked(bool)),this, SLOT(selectAll()));
    connect(ui->btnAdd_1,SIGNAL(clicked(bool)),this, SLOT(add()));
    connect(ui->btnDel_1,SIGNAL(clicked(bool)),this, SLOT(del()));

    // Количество столбцов
    ui->twTours->setColumnCount(8);
    // Возможность прокрутки
    ui->twTours->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twTours->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twTours->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
    ui->twTours->setHorizontalHeaderItem(0,new QTableWidgetItem("Название"));
    ui->twTours->setHorizontalHeaderItem(1,new QTableWidgetItem("Время начала"));
    ui->twTours->setHorizontalHeaderItem(2,new QTableWidgetItem("Время конца"));
    ui->twTours->setHorizontalHeaderItem(3,new QTableWidgetItem("Дата"));
    ui->twTours->setHorizontalHeaderItem(4,new QTableWidgetItem("Цена билета"));
    ui->twTours->setHorizontalHeaderItem(5,new QTableWidgetItem("Продажи"));
    ui->twTours->setHorizontalHeaderItem(6,new QTableWidgetItem("Группа"));
    ui->twTours->setHorizontalHeaderItem(7,new QTableWidgetItem("Место"));
    // Последний столбец растягивается при изменении размера формы
    ui->twTours->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twTours->setSortingEnabled(true);
    //ui->twTours->sortByColumn(0);   ЭТА СТРОКА ЛОМАЕТ ВЫВОД ЗАПИСЕЙ
    // Запрет на изменение ячеек таблицы при отображении
    //ui->twTours->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Tours::~Tours()
{
    if( dbconn.isOpen())
        dbconn.close();
    delete ui;
}



void Tours::dbconnect(){
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






void Tours::selectAll(){
    // Очистить содержимое компонента
    ui->twTours->clearContents();
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
    QString sqlstr = "select * from tours";
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
    ui->twTours->setRowCount( query.size());
    else
    ui->twTours->setRowCount( 0);
    ui->teResult->append( QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next())
    {
        ui->twTours->setItem(i,0,new
        QTableWidgetItem(query.value("tour_name").toString()));
        ui->twTours->setItem(i,1,new
        QTableWidgetItem(query.value("start_time").toString()));
        ui->twTours->setItem(i,2,new
        QTableWidgetItem(query.value("end_time").toString()));
        ui->twTours->setItem(i,3,new
        QTableWidgetItem(query.value("tour_date").toString()));
        ui->twTours->setItem(i,4,new
        QTableWidgetItem(query.value("ticket_price").toString()));
        ui->twTours->setItem(i,5,new
        QTableWidgetItem(query.value("amount_sold_tickets").toString()));
        ui->twTours->setItem(i,6,new
        QTableWidgetItem(query.value("band_id").toString()));
        ui->twTours->setItem(i,7,new
        QTableWidgetItem(query.value("place_id").toString()));

        i++;
    }
}





void Tours::add()
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
    QString sqlstr = "insert into tours (tour_name, start_time, end_time, tour_date, ticket_price, amount_sold_tickets, band_id, place_id) values (?,?,?,?,?,?,?,?)";

    // Подготовить запрос
    query.prepare(sqlstr);
    // Передать параметры из полей ввода в запрос
    query.bindValue(0,ui->leName->text());
    query.bindValue(1,ui->leStartTime->text());
    query.bindValue(2,ui->leEndTime->text());
    query.bindValue(3,ui->leDate->text());
    query.bindValue(4,ui->lePrice->text());
    query.bindValue(5,ui->leSoldTickets->text());
    query.bindValue(6,ui->leBand->text());
    query.bindValue(7,ui->lePlace->text());
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






void Tours::del(){
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
    int currow = ui->twTours->currentRow();
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
    QString sqlstr = "delete from tours where tour_name = '"
    + ui->twTours->item(currow,0)->text() + "'";
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

