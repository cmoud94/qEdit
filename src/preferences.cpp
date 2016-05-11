/**
    qEdit - Lightweight IDE
    Copyright (C) 2016  Marek Kouřil

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "preferences.h"
#include "mainwindow.h"

//*****************************************************************************
Preferences::Preferences ( MainWindow* parent )
{
    m_settings = new QSettings ( m_company, m_application, this );

    m_config_keys = new QList< QString >( { "text_wrap", "text_wrap_whole_words",
                                            "show_line_numbers", "highlight_current_line",
                                            "font",
                                            "tab_width" } );
    // TODO: Change to fit Qt!
    m_config_default_values = new QList< QVariant >( { 1, 1, 1, 1,
                                                       "Ubuntu,10",
                                                       4 } );

    m_config_values = new QList< QVariant >( );

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

    connect ( m_text_wrap_chkbox, SIGNAL ( stateChanged ( int ) ), this, SLOT ( config_save ( ) ) );
    connect ( m_text_wrap_words_chkbox, SIGNAL ( stateChanged ( int ) ), this, SLOT ( config_save ( ) ) );
    connect ( m_ln_nums_chkbox, SIGNAL ( stateChanged ( int ) ), this, SLOT ( config_save ( ) ) );
    connect ( m_curr_ln_chkbox, SIGNAL ( stateChanged ( int ) ), this, SLOT ( config_save ( ) ) );
    connect ( m_tab_width_spinbox, SIGNAL ( valueChanged ( int ) ), this, SLOT ( config_save ( ) ) );

    connect ( m_font_config_btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( font_config ( ) ) );

    config_read ( );
}

//*****************************************************************************
Preferences::~Preferences ( )
{
    delete m_config_keys;
    delete m_config_default_values;
    delete m_config_values;
}

//*****************************************************************************
void Preferences::config_save ( )
{
    get_widgets_values ( );

    m_settings->beginGroup ( "General" );

    for ( int i = 0; i < m_config_keys->size ( ); i++ )
    {
        m_settings->setValue ( m_config_keys->at ( i ), m_config_values->at ( i ) );
    }

    m_settings->endGroup ( );
}

//*****************************************************************************
void Preferences::font_config ( )
{
    bool ok;
    QFont font = QFontDialog::getFont ( &ok, this );

    if ( ok )
    {
        m_config_values->insert ( m_config_keys->indexOf ( "font" ), font.toString ( ) );
        config_save ( );
        update_widgets ( );
    }
}

//*****************************************************************************
void Preferences::config_read ( )
{
    m_config_values->clear ( );

    m_settings->beginGroup ( "General" );

    for ( int i = 0; i < m_config_keys->size ( ); i++ )
    {
        m_config_values->append ( m_settings->value ( m_config_keys->at ( i ), m_config_default_values->at ( i ) ).toString ( ) );
    }

    m_settings->endGroup ( );

    update_widgets ( );
}

//*****************************************************************************
void Preferences::update_widgets ( )
{
    m_settings->beginGroup ( "General" );

    m_text_wrap_chkbox->setChecked (
            m_settings->value (
                    m_config_keys->at ( m_config_keys->indexOf ( "text_wrap" ) ), m_config_default_values->at ( 0 )
                    ).toBool ( )
            );

    m_text_wrap_words_chkbox->setChecked (
            m_settings->value (
                    m_config_keys->at ( m_config_keys->indexOf ( "text_wrap_whole_words" ) ), m_config_default_values->at ( 1 )
                    ).toBool ( )
            );

    m_ln_nums_chkbox->setChecked (
            m_settings->value (
                    m_config_keys->at ( m_config_keys->indexOf ( "show_line_numbers" ) ), m_config_default_values->at ( 2 )
                    ).toBool ( )
            );

    m_curr_ln_chkbox->setChecked (
            m_settings->value (
                    m_config_keys->at ( m_config_keys->indexOf ( "highlight_current_line" ) ), m_config_default_values->at ( 3 )
                    ).toBool ( )
            );

    m_tab_width_spinbox->setValue (
            m_settings->value (
                    m_config_keys->at ( m_config_keys->indexOf ( "tab_width" ) ), m_config_default_values->at ( 5 ) ).toInt ( ) );

    QStringList sl = m_settings->value (
            m_config_keys->at ( m_config_keys->indexOf ( "font" ) ), m_config_default_values->at ( m_config_keys->indexOf ( "font" ) )
            ).toString ( ).split ( ",", QString::SkipEmptyParts );

    m_font_config_btn->setText ( sl.at ( 0 ) + " | " + sl.at ( 1 ) );

    m_settings->endGroup ( );
}

//*****************************************************************************
void Preferences::get_widgets_values ( )
{
    m_config_values->replace ( m_config_keys->indexOf ( "text_wrap" ), ( m_text_wrap_chkbox->isChecked ( ) ) ? 1 : 0 );

    m_config_values->replace ( m_config_keys->indexOf ( "text_wrap_whole_words" ), ( m_text_wrap_words_chkbox->isChecked ( ) ) ? 1 : 0 );

    m_config_values->replace ( m_config_keys->indexOf ( "show_line_numbers" ), ( m_ln_nums_chkbox->isChecked ( ) ) ? 1 : 0 );

    m_config_values->replace ( m_config_keys->indexOf ( "highlight_current_line" ), ( m_curr_ln_chkbox->isChecked ( ) ) ? 1 : 0 );

    m_config_values->replace ( m_config_keys->indexOf ( "tab_width" ), ( QString::number ( m_tab_width_spinbox->value ( ) ) ) );
}
