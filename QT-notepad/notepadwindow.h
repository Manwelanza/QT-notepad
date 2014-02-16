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


/*
 * REPARAR:
 * Una forma mejor de hacer el mensaje de ayuda
 * Que la fuente no se aplique a lo que escribo despues
 * Lo mismo que pasa con la fuente, con la negrita, cursiva y subrayado
 */

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alAcercade();
    void alNegrita();
    void alCursiva();
    void alSubrayado();

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



};

#endif // NOTEPADWINDOW_H
