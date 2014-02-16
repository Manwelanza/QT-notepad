#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QClipboard>
#include <QKeySequence>
//incluidas por mi
#include <QMessageBox>
#include <QToolBar>
#include <QWidget>

//ECHO TODO LO PROPUESTO PARA CLASE
//ECHO TODO LO PROOPUESTO PARA CASA
//ADEMAS AÑADIDO LA OPCION DE GUARDAR COMO Y GUARDAR

/*Por Arreglar:
 * Mejorar el mensaje de ayuda
*/





class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardarComo();
    void alFuente();
    void alAcercade();
    void alNegrita();
    void alCursiva();
    void alSubrayado();
    void alGuardar();

private:
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QAction* actArchivoAbrir_;
    QAction* actArchivoGuardar_;
    QMenu* mnuFormato_;
    QAction* actFormatoFuente_;
    QMenu* mnuEditar_;
    QAction* actEditarCopiar_;
    QAction* actEditarPegar_;
    QTextEdit* txtEditor_;
    QClipboard * portapapeles_;
    //por mi
    QAction* actArchivoCerrar_;
    QAction* actEditarCortar_;
    QAction* actEditarDeshacer_;
    QAction* actEditarRehacer_;
    QMenu* mnuAyuda_;
    QAction* actAyudaAcercade_;
    QToolBar* toolbarMenu_;
    QAction* actToolBarNegrita_;
    QAction* actToolBarCursiva_;
    QAction* actToolBarSubrayado_;
    QString ActualFich_;
    QAction* actArchivoGuardarComo_;



};

#endif // NOTEPADWINDOW_H
