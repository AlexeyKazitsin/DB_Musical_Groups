#include "albums.h"
#include "ui_albums.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>

Albums::Albums(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Albums)
{
    ui->setupUi(this);

    connect(ui->btnConnect_2,SIGNAL(clicked(bool)),this, SLOT(dbconnect()));
    connect(ui->btnSelectAll_2,SIGNAL(clicked(bool)),this, SLOT(selectAll()));
    connect(ui->btnAdd_2,SIGNAL(clicked(bool)),this, SLOT(add()));
    connect(ui->btnDel_2,SIGNAL(clicked(bool)),this, SLOT(del()));

    // Количество столбцов
    ui->twAlbums->setColumnCount(2);
    // Возможность прокрутки
    ui->twAlbums->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twAlbums->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twAlbums->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
    ui->twAlbums->setHorizontalHeaderItem(0,new QTableWidgetItem("Название"));
    ui->twAlbums->setHorizontalHeaderItem(1,new QTableWidgetItem("Дата выхода"));

    // Последний столбец растягивается при изменении размера формы
    ui->twAlbums->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twAlbums->setSortingEnabled(true);
    //ui->twAlbums->sortByColumn(0);   ЭТА СТРОКА ЛОМАЕТ ВЫВОД ЗАПИСЕЙ
    // Запрет на изменение ячеек таблицы при отображении
    //ui->twAlbums->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Albums::~Albums()
{
    if( dbconn.isOpen())
        dbconn.close();
    delete ui;
}



void Albums::dbconnect(){
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






void Albums::selectAll(){
    // Очистить содержимое компонента
    ui->twAlbums->clearContents();
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
    QString sqlstr = "select * from albums";
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
    ui->twAlbums->setRowCount( query.size());
    else
    ui->twAlbums->setRowCount( 0);
    ui->teResult->append( QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next())
    {
        ui->twAlbums->setItem(i,0,new
        QTableWidgetItem(query.value("album_name").toString()));
        ui->twAlbums->setItem(i,1,new
        QTableWidgetItem(query.value("release_date").toString()));

        i++;
    }
}





void Albums::add()
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
    QString sqlstr = "insert into albums (album_name, release_date) values (?,?)";

    // Подготовить запрос
    query.prepare(sqlstr);
    // Передать параметры из полей ввода в запрос
    query.bindValue(0,ui->leAlbumName->text());
    query.bindValue(1,ui->leReleaseDate->text());

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






void Albums::del(){
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
    int currow = ui->twAlbums->currentRow();
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
    QString sqlstr = "delete from albums where album_name = '"
    + ui->twAlbums->item(currow,0)->text() + "'";
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

