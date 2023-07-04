#include "songs.h"
#include "ui_songs.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>

Songs::Songs(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Songs)
{
    ui->setupUi(this);

    connect(ui->btnConnect_1,SIGNAL(clicked(bool)),this, SLOT(dbconnect()));
    connect(ui->btnSelectAll_1,SIGNAL(clicked(bool)),this, SLOT(selectAll()));
    connect(ui->btnAdd_4,SIGNAL(clicked(bool)),this, SLOT(add()));
    connect(ui->btnDel_4,SIGNAL(clicked(bool)),this, SLOT(del()));

    // Количество столбцов
    ui->twSongs->setColumnCount(5);
    // Возможность прокрутки
    ui->twSongs->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twSongs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twSongs->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
    ui->twSongs->setHorizontalHeaderItem(0,new QTableWidgetItem("Название"));
    ui->twSongs->setHorizontalHeaderItem(1,new QTableWidgetItem("Альбом"));
    ui->twSongs->setHorizontalHeaderItem(2,new QTableWidgetItem("Композитор"));
    ui->twSongs->setHorizontalHeaderItem(3,new QTableWidgetItem("Автор текста"));
    ui->twSongs->setHorizontalHeaderItem(4,new QTableWidgetItem("Группа"));
    // Последний столбец растягивается при изменении размера формы
    ui->twSongs->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twSongs->setSortingEnabled(true);
    //ui->twSongs->sortByColumn(0);   ЭТА СТРОКА ЛОМАЕТ ВЫВОД ЗАПИСЕЙ
    // Запрет на изменение ячеек таблицы при отображении
    //ui->twSongs->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Songs::~Songs()
{
    if( dbconn.isOpen())
        dbconn.close();
    delete ui;
}



void Songs::dbconnect(){
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






void Songs::selectAll(){
    // Очистить содержимое компонента
    ui->twSongs->clearContents();
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
    QString sqlstr = "select * from songs";
    //select songs.song_name, albums.album_name, people.full_name, people.full_name, bands.band_name
    //from albums join songs on albums.album_id = songs.album_id
    //join people on songs.composer_id = people.person_id
    //join bands on songs.band_id = bands.band_id
    //select songs.song_name, albums.album_name, people.full_name, people.full_name, bands.band_name from albums join songs on albums.album_id = songs.album_id join people on songs.composer_id = people.person_id join bands on songs.band_id = bands.band_id
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
    ui->twSongs->setRowCount( query.size());
    else
    ui->twSongs->setRowCount( 0);
    ui->teResult->append( QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next())
    {
        ui->twSongs->setItem(i,0,new
        QTableWidgetItem(query.value("song_name").toString()));
        ui->twSongs->setItem(i,1,new
        QTableWidgetItem(query.value("album_id").toString()));
        ui->twSongs->setItem(i,2,new
        QTableWidgetItem(query.value("composer_id").toString()));
        ui->twSongs->setItem(i,3,new
        QTableWidgetItem(query.value("songwriter_id").toString()));
        ui->twSongs->setItem(i,4,new
        QTableWidgetItem(query.value("band_id").toString()));

        i++;
    }
}





void Songs::add()
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
    QString sqlstr = "insert into songs (song_name, album_id, composer_id, songwriter_id, band_id) values (?,?,?,?,?)";

    // Подготовить запрос
    query.prepare(sqlstr);
    // Передать параметры из полей ввода в запрос
    query.bindValue(0,ui->leName_4->text());
    query.bindValue(1,ui->leAlbum->text());
    query.bindValue(2,ui->leComposer->text());
    query.bindValue(3,ui->leSongwriter->text());
    query.bindValue(4,ui->leBand_4->text());
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






void Songs::del(){
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
    int currow = ui->twSongs->currentRow();
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
    QString sqlstr = "delete from songs where song_name = '"
    + ui->twSongs->item(currow,0)->text() + "'";
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

