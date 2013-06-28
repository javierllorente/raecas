/*
 *  raecas - Plasmoide para consultar el diccionario castellano de la RAE
 *
 *  Copyright (C) 2013 Javier Llorente <javier@opensuse.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef RAECAS_HEADER
#define RAECAS_HEADER

#include <Plasma/PopupApplet>
#include <Plasma/DataEngine>
#include <libqrae.h>

class QGraphicsLinearLayout;

namespace Plasma
{
    class IconWidget;
    class LineEdit;
    class WebView;
}
 
class RaeCas : public Plasma::PopupApplet
{
    Q_OBJECT
    public:
        RaeCas(QObject *parent, const QVariantList &args);
        ~RaeCas();
	QGraphicsWidget *graphicsWidget();
	void init();
	
  protected slots:
	void consultar();
	void errorAlCargar();
	void showWebView(bool);
	void loadingWebView(int);
 
    private:
	QGraphicsWidget *m_graphicsWidget;
	QGraphicsLinearLayout *m_layout;
	QGraphicsLinearLayout *m_horLayout;
	Plasma::LineEdit *m_wordEdit;
	Plasma::WebView *m_webView;
	Plasma::IconWidget *m_iconWidget;
	DRAE *m_drae;
	QTimer *m_timer;
};

#endif