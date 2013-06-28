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

#include "raecas.h"

#include <QGraphicsLinearLayout>
#include <QTimer>

#include <KIcon>
#include <KWebView>
#include <KLineEdit>

#include <Plasma/LineEdit>
#include <Plasma/WebView>
#include <Plasma/IconWidget>

using namespace Plasma;
 
 
RaeCas::RaeCas(QObject *parent, const QVariantList &args)
    : Plasma::PopupApplet(parent, args),
    m_graphicsWidget(0),
    m_wordEdit(0)
    
{  
    setPopupIcon(QLatin1String( "qrae" ));
    setAspectRatioMode(Plasma::IgnoreAspectRatio);    
} 
 
RaeCas::~RaeCas()
{

}

void RaeCas::init()
{
   m_drae = new DRAE();
}

QGraphicsWidget *RaeCas::graphicsWidget()
{
    if (m_graphicsWidget) {
        return m_graphicsWidget;
    }
    
    m_wordEdit = new LineEdit(this);
    m_wordEdit->nativeWidget()->setClearButtonShown( true );
    m_wordEdit->nativeWidget()->setClickMessage(i18n("Enter word to define here"));
    m_wordEdit->show();
    
    m_iconWidget = new Plasma::IconWidget(this);
    m_iconWidget->setIcon(QLatin1String( "qrae" ));

    m_webView = new WebView();
    m_webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_webView->hide();
    
    m_timer = new QTimer(this);
    
    m_horLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    m_horLayout->addItem(m_wordEdit);
    m_horLayout->addItem(m_iconWidget);
    m_horLayout->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
 
    m_layout = new QGraphicsLinearLayout(Qt::Vertical);
    m_layout->addItem(m_horLayout);
    m_layout->addItem(m_webView); 
    
    connect(m_webView, SIGNAL(loadFinished(bool)), this, SLOT(showWebView(bool)));
    connect(m_webView, SIGNAL(loadProgress(int)), this, SLOT(loadingWebView(int)));    
    connect(m_wordEdit, SIGNAL(editingFinished()), this, SLOT(consultar()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(errorAlCargar()));
    
    m_graphicsWidget = new QGraphicsWidget(this);
    m_graphicsWidget->setLayout(m_layout);
    m_graphicsWidget->setPreferredSize(400, 300);
    
    return m_graphicsWidget;
}

void RaeCas::showWebView(bool ok) {

    if (ok) {      
      m_wordEdit->nativeWidget()->clear();
      m_iconWidget->setOpacity(1.0);
      
    } else {      
      errorAlCargar();
      
    }
    
    if (!m_webView->isVisible()) {
      m_webView->show();
    }
    
}

void RaeCas::loadingWebView(int progress) {
  
  float opacity = 0.2;
  int timeoutInterval = 10000;
  
  if (progress<30) {
      opacity = 0.3;
      
    } else {
      opacity = 0.6;
      
    }    
    m_iconWidget->setOpacity(opacity);

    
    if (progress!=100 && !m_timer->isActive()) {      
      m_timer->setSingleShot(true);
      m_timer->start(timeoutInterval);

    } else if (progress==100) {
        m_timer->stop();
    }
}

void RaeCas::consultar()
{  
      if (m_wordEdit->text()!="") {
	m_webView->setUrl( KUrl( m_drae->consultar( m_wordEdit->text() ) ) );
      }
}

void RaeCas::errorAlCargar()
{
      m_webView->setHtml( m_drae->getErrorMsg() );
} 

K_EXPORT_PLASMA_APPLET(raecas, RaeCas)
 
#include "raecas.moc"