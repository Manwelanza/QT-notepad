#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Editor QTextEdit"));

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this); //Ponemos el menu arriba

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);//añadimos archivo a la barra de menu de arriba

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    //La & es para que aparezla la rayita debajo de la letra que le sigue y poder darle con alt+A (en este caso)
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoGuardar_);

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);

    //Inicializamos el editor de texto
    txtEditor_ = new QTextEdit(this);

    //Conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_, SIGNAL(triggered()), this, SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this, SLOT(alGuardar()));
    connect(actEditarCopiar_, SIGNAL(triggered()), txtEditor_, SLOT(copy()));
    connect(actEditarPegar_, SIGNAL(triggered()), txtEditor_, SLOT(paste()));
    connect(actFormatoFuente_, SIGNAL(triggered()), this, SLOT(alFuente()));

    //Agregamos el editor de texto a la ventana
    this->setCentralWidget(txtEditor_);

    //Por mi CERRAR
    actArchivoCerrar_ = new QAction(tr("&Cerrar"), this);
    mnuArchivo_->addAction(actArchivoCerrar_);

    connect(actArchivoCerrar_, SIGNAL(triggered()),this,SLOT(close()));

    //Por mi CORTAR
    actEditarCortar_ = new QAction(tr("&Cortar"),this);
    mnuEditar_->addAction(actEditarCortar_);

    connect(actEditarCortar_, SIGNAL(triggered()), txtEditor_, SLOT(cut()));

    //Por mi deshacer
    actEditarDeshacer_ = new QAction(tr("&Deshacer"),this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarDeshacer_);

    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_, SLOT(undo()));

    //Por mi rehacer

    actEditarRehacer_ = new QAction(tr("&Rehacer"),this);
    mnuEditar_->addAction(actEditarRehacer_);

    connect(actEditarRehacer_, SIGNAL(triggered()), txtEditor_, SLOT(redo()));

    //Por mi ayuda/acerca de
    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcercade_ = new QAction(tr("&Acerca de"),this);
    mnuAyuda_->addAction(actAyudaAcercade_);

    connect(actAyudaAcercade_, SIGNAL(triggered()), this, SLOT(alAcercade()));

    //Por mi toolbar
    toolbarMenu_ = new QToolBar(this);
    this->addToolBar(toolbarMenu_);

    actToolbarGuardar_ = new QAction(tr("S"),this);
    toolbarMenu_->addAction(actToolbarGuardar_);
    connect(actToolbarGuardar_, SIGNAL(triggered()), this, SLOT(alGuardar()));

    actToolbarCopiar_ = new QAction(tr("C"),this);
    toolbarMenu_->addAction(actToolbarCopiar_);
    connect(actToolbarCopiar_, SIGNAL(triggered()), txtEditor_, SLOT(copy()));

    actToolbarPegar_ = new QAction(tr("P"),this);
    toolbarMenu_->addAction(actToolbarPegar_);
    connect(actToolbarPegar_, SIGNAL(triggered()), txtEditor_, SLOT(paste()));

    actToolbarDeshacer_ = new QAction(tr("<-"),this);
    toolbarMenu_->addAction(actToolbarDeshacer_);
    connect(actToolbarDeshacer_, SIGNAL(triggered()), txtEditor_, SLOT(undo()));

    actToolbarRehacer_ = new QAction(tr("->"),this);
    toolbarMenu_->addAction(actToolbarRehacer_);
    connect(actToolbarRehacer_, SIGNAL(triggered()), txtEditor_, SLOT(redo()));

}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    mnuArchivo_->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    txtEditor_->deleteLater();
    //Por mi
    mnuAyuda_->deleteLater();
    actAyudaAcercade_->deleteLater();
    toolbarMenu_->deleteLater();
    actToolbarCopiar_->deleteLater();
    actToolbarPegar_->deleteLater();
    actToolbarGuardar_->deleteLater();
    actToolbarDeshacer_->deleteLater();
    actToolbarRehacer_->deleteLater();
}

void NotepadWindow::alAbrir()
{
    //Mostramos un dialogo de apertura de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,tr("Abrir archivo de texto plano"),"",tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly)) {
            //Si se pudo abrir el archivo, lo leemos y colocamos su contenido en nuestro editor
            txtEditor_->setPlainText(archivo.readAll());
            archivo.close();
        }
    }
}

void NotepadWindow::alGuardar()
{
    //Mostramos un dialogo de guardado de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,tr("Guardar archivo de texto plano"),"",tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo + ".txt");
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8());
            archivo.close(); //cerramos el fichero
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setCurrentFont(font);

        //Se aplica solo a lo seleccionado, PERO tambien a lo que escribas despues
        //El fallo posiblemente este en la forma de aplicar a setCurrentFont, que se lo aplico a lo seleccionado, pero tambien lo dejo como
        //fuente de todo txtEditor_ menos de lo que ya estaba escrito pero no seleccionado que no cambia
    }
}

void NotepadWindow::alAcercade()
{

    QMessageBox msgBox;
    msgBox.setText("Esto es un editor de texto \nEnserio necesitas más ayuda?");
    msgBox.exec();

    //Intento con error de crear una ventana con el mensaje ayuda
    //EL fallo, o uno de ellos esta en el connect, posiblemente con el this

    /*QWidget mensajeAyuda;
    mensajeAyuda.resize(400,300);
    mensajeAyuda.setWindowTitle(tr("Ventana de ayuda"));
    QLabel etiqueta("Cosas de ayuda", &mensajeAyuda);
    QPushButton ok("ok", &mensajeAyuda);
    ok.setFont(QFont("Times",18,QFont::Bold));
    ok.setGeometry(180,280,200,290);
    connect(&ok,SIGNAL(clicked()),this,SLOT(quit()));

    mensajeAyuda.show();
    */

}
