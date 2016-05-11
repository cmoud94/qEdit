#include <stdio.h>
#include <stdlib.h>

#include "preferences.h"
#include "mainwindow.h"

//*****************************************************************************
Preferences::Preferences ( MainWindow* parent )
{
    m_config_keys = new QList< QString >( { "text_wrap", "text_wrap_whole_words",
                                            "show_line_numbers", "highlight_current_line",
                                            "font_family", "font_size", "font_weight",
                                            "tab_width", "geometry" } );
    // TODO: Change to fit Qt!
    m_config_default_values = new QList< QString >( { "1", "1", "1", "1",
                                                      "Monospace", "10", "normal",
                                                      "4", "800x500+0+0" } );

    m_config_values = new QList< QString >( );

    // GUI init
    m_layout = new QVBoxLayout (  );

    //*************************************************************************

    m_text_wrap_group = new QGroupBox ( "Text wrapping" );

    m_text_wrap_chkbox = new QCheckBox ( "Enable text wrapping" );

    m_text_wrap_words_chkbox = new QCheckBox ( "Wrap whole words" );

    QVBoxLayout* lay = new QVBoxLayout ( );

    lay->addWidget ( m_text_wrap_chkbox );

    lay->addWidget ( m_text_wrap_words_chkbox );

    m_text_wrap_group->setLayout ( lay );

    m_layout->addWidget ( m_text_wrap_group );

    //*************************************************************************

    m_ln_nums_group = new QGroupBox ( "Line numbers" );

    m_ln_nums_chkbox = new QCheckBox ( "Show line numbers" );

    lay = new QVBoxLayout ( );

    lay->addWidget ( m_ln_nums_chkbox );

    m_ln_nums_group->setLayout ( lay );

    m_layout->addWidget ( m_ln_nums_group );

    //*************************************************************************

    m_curr_ln_group = new QGroupBox ( "Current line" );

    m_curr_ln_chkbox = new QCheckBox ( "Highlight current line" );

    lay = new QVBoxLayout ( );

    lay->addWidget ( m_curr_ln_chkbox );

    m_curr_ln_group->setLayout ( lay );

    m_layout->addWidget ( m_curr_ln_group );

    //*************************************************************************

    m_tab_width_group = new QGroupBox ( "Tab width" );

    m_tab_width_spinbox = new QSpinBox ( );

    lay = new QVBoxLayout ( );

    lay->addWidget ( m_tab_width_spinbox );

    m_tab_width_group->setLayout ( lay );

    m_layout->addWidget ( m_tab_width_group );

    //*************************************************************************

    m_font_config_group = new QGroupBox ( "Font settings" );

    m_font_config_btn = new QPushButton ( "Font settings" );

    lay = new QVBoxLayout ( );

    lay->addWidget ( m_font_config_btn );

    m_font_config_group->setLayout ( lay );

    m_layout->addWidget ( m_font_config_group );

    //*************************************************************************

    setLayout ( m_layout );

    setModal ( true );

    show ( );

    setFixedWidth ( width ( ) + 100 );

    setFixedHeight ( height ( ) );

    read_config_file ( );

    connect ( m_text_wrap_chkbox, SIGNAL ( stateChanged ( int ) ), this, SLOT ( write_config_file ( ) ) );
    connect ( m_text_wrap_words_chkbox, SIGNAL ( stateChanged ( int ) ), this, SLOT ( write_config_file ( ) ) );
    connect ( m_ln_nums_chkbox, SIGNAL ( stateChanged ( int ) ), this, SLOT ( write_config_file ( ) ) );
    connect ( m_curr_ln_chkbox, SIGNAL ( stateChanged ( int ) ), this, SLOT ( write_config_file ( ) ) );
    connect ( m_tab_width_spinbox, SIGNAL ( valueChanged ( int ) ), this, SLOT ( write_config_file ( ) ) );
}

//*****************************************************************************
Preferences::~Preferences ( )
{
    delete m_config_keys;
    delete m_config_default_values;
    delete m_config_values;
}

//*****************************************************************************
void Preferences::write_config_file ( )
{
    get_widgets_values ( );

    QFile f ( m_config_file_path );

    if ( !f.open ( QFile::WriteOnly | QFile::Text ) )
    {
        printf ( "%s: Can't write config file.\n", __FUNCTION__ );
        return;
    }

    QTextStream out ( &f );

    for ( int i = 0; i < m_config_keys->size ( ); i++ )
    {
        out << m_config_keys->at ( i ) << "=" << m_config_values->at ( i ) << "\n";
    }

    f.close ( );
}

//*****************************************************************************
void Preferences::read_config_file ( )
{
    QFile f ( m_config_file_path );

    if ( !f.open ( QFile::ReadOnly | QFile::Text ) )
    {
        printf ( "%s: Can't read config file.\n", __FUNCTION__ );
        return;
    }

    QTextStream in ( &f );

    QString config = in.readAll ( );

    f.close ( );

    QStringList conf_list = config.split ( "\n", QString::SkipEmptyParts );

    for ( int i = 0; i < conf_list.size ( ); i++ )
    {
        QStringList conf_line = conf_list.at ( i ).split ( "=" );
        m_config_values->append ( conf_line.at ( 1 ) );
    }

    update_widgets ( );
}

//*****************************************************************************
void Preferences::update_widgets ( )
{
    for ( int i = 0; i < m_config_values->size ( ); i++ )
    {
        switch ( i )
        {
            case 0:
                if ( m_config_values->at ( i ).toInt ( ) == 1 )
                {
                    m_text_wrap_chkbox->setCheckState ( Qt::Checked );
                }
                else
                {
                    m_text_wrap_chkbox->setCheckState ( Qt::Unchecked );
                }
                break;
            case 1:
                if ( m_config_values->at ( i ).toInt ( ) == 1 )
                {
                    m_text_wrap_words_chkbox->setCheckState ( Qt::Checked );
                }
                else
                {
                    m_text_wrap_words_chkbox->setCheckState ( Qt::Unchecked );
                }
                break;
            case 2:
                if ( m_config_values->at ( i ).toInt ( ) == 1 )
                {
                    m_ln_nums_chkbox->setCheckState ( Qt::Checked );
                }
                else
                {
                    m_ln_nums_chkbox->setCheckState ( Qt::Unchecked );
                }
                break;
            case 3:
                if ( m_config_values->at ( i ).toInt ( ) == 1 )
                {
                    m_curr_ln_chkbox->setCheckState ( Qt::Checked );
                }
                else
                {
                    m_curr_ln_chkbox->setCheckState ( Qt::Unchecked );
                }
                break;
            case 4:
                m_font_config_btn->setText ( m_config_values->at ( i ) );
                break;
            case 5:
                m_font_config_btn->setText ( m_font_config_btn->text ( ) + " | " + m_config_values->at ( i ) );
                break;
            case 7:
                m_tab_width_spinbox->setValue ( m_config_values->at ( i ).toInt ( ) );
                break;
            default:
                break;
        }
    }
}

//*****************************************************************************
void Preferences::get_widgets_values ( )
{
    for ( int i = 0; i < m_config_values->size ( ); i++ )
    {
        switch ( i )
        {
            case 0:
                m_config_values->replace ( i, ( m_text_wrap_chkbox->isChecked ( ) ) ? "1" : "0" );
                break;
            case 1:
                m_config_values->replace ( i, ( m_text_wrap_words_chkbox->isChecked ( ) ) ? "1" : "0" );
                break;
            case 2:
                m_config_values->replace ( i, ( m_ln_nums_chkbox->isChecked ( ) ) ? "1" : "0" );
                break;
            case 3:
                m_config_values->replace ( i, ( m_curr_ln_chkbox->isChecked ( ) ) ? "1" : "0" );
                break;
            case 7:
                m_config_values->replace ( i, ( QString::number ( m_tab_width_spinbox->value ( ) ) ) );
                break;
            default:
                break;
        }
    }
}
