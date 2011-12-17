/**************************************************************************
*   Copyright (C) 2010 by Michael Carpenter (malcom2073)                  *
*   mcarpenter@interforcesystems.com                                      *
*                                                                         *
*   This file is a part of OBDToolbox                                     *
*                                                                         *
*   OBDToolbox is free software: you can redistribute it and/or modify    *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation, either version 3 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   OBDToolbox is distributed in the hope that it will be useful,         *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with OBDToolbox.  If not, see <http://www.gnu.org/licenses/>.   *
***************************************************************************/
#include "gaugewidget.h"
#define M_PI 3.1415926535897932384626433832795
#include <math.h>
#include <QString>
#include <QDebug>
GaugeWidget::GaugeWidget(QWidget *parent) : QWidget(parent)
{
	m_fake = false;
	m_style = 1;
	m_fadeEnabled = false;
	setAttribute(Qt::WA_OpaquePaintEvent,true);
	resizeDraw = false;
	_scaleStartAngle = 45;
	_scaleEndAngle = 315;
	_numLabels = 10;
	_maxValue = 10000;
	_minValue = 0;
	_value = 1000;
	_bgImage = new QImage(QSize(this->width(),this->height()),QImage::Format_ARGB32);
	_reverseOrder = false;
	drawBackground();
	_danger = 0.90;
	_warning = 0.75;
	gaugeTimer = new QTimer(this);
	connect(gaugeTimer,SIGNAL(timeout()),this,SLOT(gaugeTimerTick()));

	fadeTimer = new QTimer(this);
	connect(fadeTimer,SIGNAL(timeout()),this,SLOT(fadeTimerTick()));

	needleCenterPen.setColor(QColor(0,0,0));
	needleCenterOutlinePen.setColor(QColor(100,100,100));
	needlePen.setColor(QColor(255,165,0));
	needlePen.setWidth(5);
	needleOutlinePen.setColor(QColor(255,0,0));
	needleOutlinePen.setWidth(8);

	outlinePen.setColor(QColor(255,165,0));
	outlinePen.setWidth(3);

	normalTickPen.setColor(QColor(255,165,0));
	normalTickPen.setWidth(3);
	normalBigTickPen.setColor(QColor(255,165,0));
	normalBigTickPen.setWidth(3);

	dangerTickPen.setColor(QColor(255,0,0));
	dangerTickPen.setWidth(3);
	dangerBigTickPen.setColor(QColor(255,0,0));
	dangerBigTickPen.setWidth(3);

	warningTickPen.setColor(QColor(255,255,0));
	warningTickPen.setWidth(3);
	warningBigTickPen.setColor(QColor(255,255,0));
	warningBigTickPen.setWidth(3);

	normalFontPen.setColor(QColor(255,165,0));
	dangerFontPen.setColor(QColor(255,0,0));
	warningFontPen.setColor(QColor(255,255,0));
	labelFont.setFamily("Ariel");
	labelFont.setPixelSize(20);

}
void GaugeWidget::resizeEvent (QResizeEvent *evt)
{
	Q_UNUSED(evt);
	delete _bgImage;
	_bgImage = new QImage(QSize(this->width(),this->height()),QImage::Format_ARGB32);
	drawBackground();
}
void GaugeWidget::drawBackground()
{
	if (m_style == 1)
	{
		//double ellipseA = 100;
		//double ellipseB = 75;
		int topellipsex = 1;
		int topellipsey = 1;
		int topellipsewidth=198;
		int topellipseheight=150;
		int internalWidth = width() * 0.90;
		int internalHeight = height() * 0.90;
		int widthOffset = width() * 0.05;
		int heightOffset = height() * 0.05;
		QPainter tmpPainter(_bgImage);
		tmpPainter.setRenderHint(QPainter::Antialiasing);
		tmpPainter.setBrush(Qt::SolidPattern);
		tmpPainter.drawRect(0,0,width(),height());
		tmpPainter.drawEllipse(widthOffset,heightOffset,internalWidth,internalHeight);
		//myGraphics.FillEllipse(_inFillPen.Brush, 0, 0, this.Size.Width - 1, this.Size.Height - 1);
		tmpPainter.setPen(outlinePen);
		//tmpPainter.drawEllipse(0,0,this->width()-1,this->height()-1);
		tmpPainter.drawArc(widthOffset,heightOffset,internalWidth,internalHeight,((0-_scaleStartAngle)*16) - (16*90),(0-(_scaleEndAngle - _scaleStartAngle))*16);
		//tmpPainter.setBrush(Qt::SolidPattern);
		tmpPainter.setBrush(Qt::NoBrush);
		for (int i=internalWidth;i<=(width() - ((width() - internalWidth)/2));i++)
		{
			tmpPainter.setPen(QPen(QColor(255.0 * (1.0-((float)(internalWidth - i) / (internalWidth - (width() - ((width() - internalWidth)/2))))),160.0 * (1.0-((float)(internalWidth - i) / (internalWidth - (width() - ((width() - internalWidth)/2))))),0)));
			//qDebug() << (internalWidth - i) + widthOffset << (internalWidth-i) + heightOffset << i << widthOffset << (internalWidth-i);
			//qDebug() << 255 * ((float)(internalWidth - i) / (internalWidth - (width() - ((width() - internalWidth)/2))));
			tmpPainter.drawEllipse(widthOffset+(internalWidth - i),heightOffset+(internalWidth - i),i-(internalWidth-i),i - (internalWidth-i));
		}
		int r=0;
		//int a=0;
		//int g=0;
		//int b=0;
		//RectangleF glossRect = new RectangleF((float)(this.Width * 0.075), (float)(this.Height * 0.01), (float)(this.Width * 0.85), (float)(this.Height * 0.75));
		topellipsex = (internalWidth * 0.075) +widthOffset;
		topellipsey = (internalHeight * 0.01) + heightOffset;
		topellipsewidth = internalWidth * 0.85;
		topellipseheight = internalHeight * 0.75;

		float bottomellipsex = (internalWidth * 0.25) + widthOffset;
		float bottomellipsey = (internalHeight * 0.77) + heightOffset;
		float bottomellipsewidth = internalWidth * 0.50;
		float bottomellipseheight = internalHeight * 0.2;
		//glossRect = new RectangleF((float)(this.Width * 0.25), (float)(this.Height * 0.77), (float)(this.Width * 0.50), (float)(this.Height * 0.2));
		QLinearGradient myGradient(0,topellipseheight,0,0);

		QPainterPath myPath;
		tmpPainter.setPen(QPen(QColor(0,0,0,0)));
		myPath.addEllipse(QRect(topellipsex,topellipsey,topellipsewidth,topellipseheight));
		tmpPainter.setBrush(myGradient);
		tmpPainter.drawPath(myPath);
		for (int i=bottomellipsex;i<bottomellipsex + bottomellipsewidth;i++)
		{
			for (int j=bottomellipsey;j<bottomellipsey + bottomellipseheight;j++)
			{
				if (((pow((double)(i-(bottomellipsex + (bottomellipsewidth/2))),2)/pow((double)(bottomellipsewidth/2.0),2)) + (pow((double)(j-(bottomellipsey + (bottomellipseheight/2))),2) / pow((bottomellipseheight/2.0),2))) < 1)
				{
					r = (abs(((bottomellipseheight)/2) - ((j - bottomellipsey)-((double)(bottomellipseheight) / 2.0))) / (double)(bottomellipseheight)) * 255.0;
					tmpPainter.setPen(QColor(200,200,200,255 - r));
					tmpPainter.drawPoint(i,j);
				}
			}
		}
		tmpPainter.setPen(QColor(0,0,0));
		double x=0;
		double y=0;
		for (int i = 0; i < _numLabels + ((_scaleEndAngle - _scaleStartAngle) == 360 ? 0 : 1); i++)
		{
			if (_reverseOrder)
			{
				x = (float)((cos((((_scaleEndAngle - _scaleStartAngle)) - (i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (internalWidth - (internalWidth / 3)) / 2.0)) + ((internalWidth) / 2);
				y = (float)((sin((((_scaleEndAngle - _scaleStartAngle)) - (i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (internalHeight - (internalHeight / 3)) / 2.0)) + ((internalHeight) / 2);
			}
			else
			{
				if (this->width() > 200)
				{
					x = (float)((cos(((i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (internalWidth - (internalWidth / 3)) / 2.2)) + ((internalWidth) / 2) + widthOffset;
					y = (float)((sin(((i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (internalHeight - (internalHeight / 3)) / 2.2)) + ((internalHeight) / 2) + heightOffset;
				}
				else
				{
					x = (float)((cos(((i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (this->width() - (this->width() / 3)) / 2.9)) + ((this->width()) / 2);
					y = (float)((sin(((i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (this->height() - (this->height() / 3)) / 2.9)) + ((this->height()) / 2);
				}
			}
			QString val = "";
			val = QString::number(((int)((i * ((_maxValue - _minValue) / _numLabels)) + _minValue)));
			if (((float)i / (float)_numLabels) > _danger)
			{
				tmpPainter.setPen(dangerFontPen);
			//	myGraphics.DrawString(val, _myFont, _fontDangerPen.Brush, x - (_myFont.Size / 2) * val.Length, y - (_myFont.Height / 2));
			}
			else if (((float)i / (float)_numLabels) > _warning)
			{
				tmpPainter.setPen(warningFontPen);
			//	myGraphics.DrawString(val, _myFont, _fontWarningPen.Brush, x - (_myFont.Size / 2) * val.Length, y - (_myFont.Height / 2));
			}
			else
			{
				tmpPainter.setPen(normalFontPen);
			//	myGraphics.DrawString(val, _myFont, _fontPen.Brush, x - (_myFont.Size / 2) * val.Length, y - (_myFont.Height / 2));
			}
			QFontMetrics fm(labelFont);
			tmpPainter.setFont(labelFont);
			tmpPainter.drawText(QPointF(x - (fm.width(val)/2),y+3),val);
		}


		for (int i = 0; i <= ((_numLabels) * 5); i++)
		{
			x = (float)(cos((i * ((_scaleEndAngle - _scaleStartAngle) / (_numLabels * 5.0)) + 90.0 + _scaleStartAngle) * M_PI / 180)); //* (this.Size.Width / 2) + (this.Size.Width));
			y = (float)(sin((i * ((_scaleEndAngle - _scaleStartAngle) / (_numLabels * 5.0)) + 90.0 + _scaleStartAngle) * M_PI / 180)); //* (this.Size.Height / 2) + (this.Size.Height));
			if ((i % 5) != 0)
			{
				if (((float)i / (float)(_numLabels * 5)) > _danger)
				{
					tmpPainter.setPen(dangerTickPen);
				}
				else if (((float)i / (float)(_numLabels * 5)) > _warning)
				{
					tmpPainter.setPen(warningTickPen);
				}
				else
				{
					tmpPainter.setPen(normalTickPen);
				}

				tmpPainter.drawLine(x * ((internalWidth / 2) - 10) + ((internalWidth / 2) + widthOffset), y * ((internalHeight / 2) - 10) + ((internalHeight / 2)+heightOffset),x * ((internalWidth  / 2) - 20) + ((internalWidth / 2) + widthOffset), y * ((internalHeight / 2) - 20) + ((internalHeight / 2) + heightOffset));
			}
			else
			{

				if (((float)i / (float)(_numLabels * 5)) > _danger)
				{
					tmpPainter.setPen(dangerBigTickPen);
				}
				else if (((float)i / (float)(_numLabels * 5)) > _warning)
				{
					tmpPainter.setPen(warningBigTickPen);
				}
				else
				{
					tmpPainter.setPen(normalBigTickPen);
				}
				tmpPainter.drawLine(x * ((internalWidth / 2) - 10) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - 10) + ((internalHeight / 2)+heightOffset),x * ((internalWidth  / 2) - 30) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - 30) + ((internalHeight / 2)+heightOffset));
			}
		}
		tmpPainter.end();
		if (m_fadeEnabled)
		{
			_fadedBgImage = new QImage(*_bgImage);
			_fadedBgImage->detach();
			int lineNum = 0;
			uchar *line = _fadedBgImage->scanLine(lineNum++);
			while (lineNum <= _fadedBgImage->height())
			{
				QRgb *rgb = (QRgb*)(line);
					for (int i=0;i<_fadedBgImage->width();i++)
				{
					rgb[i] = qRgba(qRed(rgb[i]),qGreen(rgb[i]),qBlue(rgb[i]),(fadeAmount / 100.0) * 255.0); //qBlue(*rgb) qAlpha(*rgb) * 0.50
				}
				line = _fadedBgImage->scanLine(lineNum++);
			}
			resizeDraw = true;
		}
	}
	else if (m_style == 2)
	{
		//double ellipseA = 100;
		//double ellipseB = 75;
		//int topellipsex = 1;
		//int topellipsey = 1;
		//int topellipsewidth=198;
		//int topellipseheight=150;
		int internalWidth = width() * 0.90;
		int internalHeight = height() * 0.90;
		int widthOffset = width() * 0.05;
		int heightOffset = height() * 0.05;

		QPainter tmpPainter(_bgImage);
		tmpPainter.setRenderHint(QPainter::Antialiasing);
		tmpPainter.setBrush(Qt::SolidPattern);
		tmpPainter.drawRect(0,0,width(),height());
		tmpPainter.drawEllipse(widthOffset,heightOffset,internalWidth,internalHeight);
		//myGraphics.FillEllipse(_inFillPen.Brush, 0, 0, this.Size.Width - 1, this.Size.Height - 1);
		tmpPainter.setPen(QPen(QColor::fromRgb(100,100,100)));
		float x=0;
		float y=0;
		for (int i = 0; i < _numLabels + ((_scaleEndAngle - _scaleStartAngle) == 360 ? 0 : 1); i++)
		{
			if (_reverseOrder)
			{
				x = (float)((cos((((_scaleEndAngle - _scaleStartAngle)) - (i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (internalWidth - (internalWidth / 3)) / 2.0)) + ((internalWidth) / 2);
				y = (float)((sin((((_scaleEndAngle - _scaleStartAngle)) - (i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (internalHeight - (internalHeight / 3)) / 2.0)) + ((internalHeight) / 2);
			}
			else
			{
				if (this->width() > 200)
				{
					x = (float)((cos(((i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (internalWidth - (internalWidth / 3)) / 2.2)) + ((internalWidth) / 2) + widthOffset;
					y = (float)((sin(((i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (internalHeight - (internalHeight / 3)) / 2.2)) + ((internalHeight) / 2) + heightOffset;
				}
				else
				{
					x = (float)((cos(((i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (this->width() - (this->width() / 3)) / 2.9)) + ((this->width()) / 2);
					y = (float)((sin(((i * ((_scaleEndAngle - _scaleStartAngle) / _numLabels)) - 270 + _scaleStartAngle) * M_PI / 180) * (this->height() - (this->height() / 3)) / 2.9)) + ((this->height()) / 2);
				}
			}
			QString val = "";
			val = QString::number(((int)((i * ((_maxValue - _minValue) / _numLabels)) + _minValue)));
			if (((float)i / (float)_numLabels) > _danger)
			{
				tmpPainter.setPen(dangerFontPen);
			//	myGraphics.DrawString(val, _myFont, _fontDangerPen.Brush, x - (_myFont.Size / 2) * val.Length, y - (_myFont.Height / 2));
			}
			else if (((float)i / (float)_numLabels) > _warning)
			{
				tmpPainter.setPen(warningFontPen);
			//	myGraphics.DrawString(val, _myFont, _fontWarningPen.Brush, x - (_myFont.Size / 2) * val.Length, y - (_myFont.Height / 2));
			}
			else
			{
				tmpPainter.setPen(QPen(QColor::fromRgb(200,200,200)));
			//	myGraphics.DrawString(val, _myFont, _fontPen.Brush, x - (_myFont.Size / 2) * val.Length, y - (_myFont.Height / 2));
			}
			QFontMetrics fm(labelFont);
			tmpPainter.setFont(labelFont);
			tmpPainter.drawText(QPointF(x - (fm.width(val)/2),y+3),val);
		}

		if (this->width() < 250)
		{
		for (int i = 0; i <= ((_numLabels) * 5); i++)
		{
			x = (float)(cos((i * ((_scaleEndAngle - _scaleStartAngle) / (_numLabels * 5.0)) + 90.0 + _scaleStartAngle) * M_PI / 180)); //* (this.Size.Width / 2) + (this.Size.Width));
			y = (float)(sin((i * ((_scaleEndAngle - _scaleStartAngle) / (_numLabels * 5.0)) + 90.0 + _scaleStartAngle) * M_PI / 180)); //* (this.Size.Height / 2) + (this.Size.Height));
			if (((i % 5) == 0) && (!((i % 20) == 0)))
			{
				if (((float)i / (float)(_numLabels * 5)) > _danger)
				{
					tmpPainter.setPen(dangerBigTickPen);
				}
				else if (((float)i / (float)(_numLabels * 5)) > _warning)
				{
					tmpPainter.setPen(warningBigTickPen);
				}
				else
				{
					tmpPainter.setPen(QPen(QColor::fromRgb(200,200,200)));
				}
				tmpPainter.drawLine(x * ((internalWidth / 2) - 10) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - 10) + ((internalHeight / 2)+heightOffset),x * ((internalWidth  / 2) - (internalWidth * 0.08)) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - (internalHeight * 0.08)) + ((internalHeight / 2)+heightOffset));
			}
			/*else if ((i % 20) == 0)
			{
				if (((float)i / (float)(_numLabels * 20)) > _danger)
				{
					tmpPainter.setPen(dangerBigTickPen);
				}
				else if (((float)i / (float)(_numLabels * 20)) > _warning)
				{
					tmpPainter.setPen(warningBigTickPen);
				}
				else
				{
					tmpPainter.setPen(QPen(QColor::fromRgb(200,200,200)));
				}
				tmpPainter.drawLine(x * ((internalWidth / 2) - 10) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - 10) + ((internalHeight / 2)+heightOffset),x * ((internalWidth  / 2) - (internalWidth * 0.1)) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - (internalHeight * 0.1)) + ((internalHeight / 2)+heightOffset));
			}*/
			else
			{
				if (((float)i / (float)(_numLabels * 5)) > _danger)
				{
					tmpPainter.setPen(dangerTickPen);
				}
				else if (((float)i / (float)(_numLabels * 5)) > _warning)
				{
					tmpPainter.setPen(warningTickPen);
				}
				else
				{
					tmpPainter.setPen(QPen(QColor::fromRgb(200,200,200)));
				}

				tmpPainter.drawLine(x * ((internalWidth / 2) - 10) + ((internalWidth / 2) + widthOffset), y * ((internalHeight / 2) - 10) + ((internalHeight / 2)+heightOffset),x * ((internalWidth  / 2) - (internalWidth * 0.05)) + ((internalWidth / 2) + widthOffset), y * ((internalHeight / 2) - (internalHeight * 0.05)) + ((internalHeight / 2) + heightOffset));
			}
		}

		}
		else
		{


		for (int i = 0; i <= ((_numLabels) * 20); i++)
		{
			x = (float)(cos((i * ((_scaleEndAngle - _scaleStartAngle) / (_numLabels * 20.0)) + 90.0 + _scaleStartAngle) * M_PI / 180)); //* (this.Size.Width / 2) + (this.Size.Width));
			y = (float)(sin((i * ((_scaleEndAngle - _scaleStartAngle) / (_numLabels * 20.0)) + 90.0 + _scaleStartAngle) * M_PI / 180)); //* (this.Size.Height / 2) + (this.Size.Height));
			if (((i % 5) == 0) && (!((i % 20) == 0)))
			{
				if (((float)i / (float)(_numLabels * 20)) > _danger)
				{
					tmpPainter.setPen(dangerBigTickPen);
				}
				else if (((float)i / (float)(_numLabels * 20)) > _warning)
				{
					tmpPainter.setPen(warningBigTickPen);
				}
				else
				{
					tmpPainter.setPen(QPen(QColor::fromRgb(200,200,200)));
				}
				tmpPainter.drawLine(x * ((internalWidth / 2) - 10) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - 10) + ((internalHeight / 2)+heightOffset),x * ((internalWidth  / 2) - (internalWidth * 0.08)) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - (internalHeight * 0.08)) + ((internalHeight / 2)+heightOffset));
			}
			else if ((i % 20) == 0)
			{
				if (((float)i / (float)(_numLabels * 20)) > _danger)
				{
					tmpPainter.setPen(dangerBigTickPen);
				}
				else if (((float)i / (float)(_numLabels * 20)) > _warning)
				{
					tmpPainter.setPen(warningBigTickPen);
				}
				else
				{
					tmpPainter.setPen(QPen(QColor::fromRgb(200,200,200)));
				}
				tmpPainter.drawLine(x * ((internalWidth / 2) - 10) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - 10) + ((internalHeight / 2)+heightOffset),x * ((internalWidth  / 2) - (internalWidth * 0.1)) + ((internalWidth / 2)+widthOffset), y * ((internalHeight / 2) - (internalHeight * 0.1)) + ((internalHeight / 2)+heightOffset));
			}
			else
			{
				if (((float)i / (float)(_numLabels * 20)) > _danger)
				{
					tmpPainter.setPen(dangerTickPen);
				}
				else if (((float)i / (float)(_numLabels * 20)) > _warning)
				{
					tmpPainter.setPen(warningTickPen);
				}
				else
				{
					tmpPainter.setPen(QPen(QColor::fromRgb(200,200,200)));
				}

				tmpPainter.drawLine(x * ((internalWidth / 2) - 10) + ((internalWidth / 2) + widthOffset), y * ((internalHeight / 2) - 10) + ((internalHeight / 2)+heightOffset),x * ((internalWidth  / 2) - (internalWidth * 0.05)) + ((internalWidth / 2) + widthOffset), y * ((internalHeight / 2) - (internalHeight * 0.05)) + ((internalHeight / 2) + heightOffset));
			}
		}
		}

	}
}
void GaugeWidget::paintEvent(QPaintEvent *evt)
{
	Q_UNUSED(evt);
	if (m_style == 1)
	{
		QPainter tmpPainter(this);
		if (m_fake)
		{
			tmpPainter.setBrush(Qt::SolidPattern);
			tmpPainter.drawRect(0,0,width(),height());
			resizeDraw = true;
		}

		//tmpPainter.setRenderHint(QPainter::Antialiasing);
		//tmpPainter.drawLine(0,0,this->width()-1,0);
		double _valueInRadi = (((_value * ((_scaleEndAngle - _scaleStartAngle)/(_maxValue-_minValue))) + 90 + _scaleStartAngle) * (M_PI / 180.0));
		//tmpPainter.drawLine(this->width()-1,0,this->width()-1,this->height()-1);
		//tmpPainter.drawLine(this->width()-1,this->height()-1,0,this->height()-1);
		//tmpPainter.drawLine(0,0,0,this->height()-1);
		if (m_fadeEnabled)
		{
			if (resizeDraw)
			{
				tmpPainter.drawImage(0,0,*_bgImage);
				resizeDraw = false;
			}
			else
			{
				tmpPainter.drawImage(0,0,*_fadedBgImage);
			}
		}
		else
		{
			tmpPainter.drawImage(0,0,*_bgImage);
		}
		double x=0;
		double y=0;
	//if (_reverseOrder)
	//{
	//x = (float)(0 + (((this.Width / 2) - 31) * Math.Cos((0 * Math.PI / 180) - _valueInRadi) * Math.Cos(0 * Math.PI / 180)) - (((this.Width / 2) - 31) * Math.Sin((0 * Math.PI / 180) - _valueInRadi) * Math.Sin(0 * Math.PI / 180)));
	//y = (float)(0 + (((this.Height / 2) - 31) * Math.Sin((0 * Math.PI / 180) - _valueInRadi) * Math.Cos(0 * Math.PI / 180)) + (((this.Height / 2) - 31) * Math.Cos((0 * Math.PI / 180) - _valueInRadi) * Math.Sin(0 * Math.PI / 180)));
	//}
	//else
	//{
	////float x = (this.Size.Width / 2) + ((this.Height) * Math.Cos(_valueInRadi) * cosbeta - b * sinalpha * sinbeta);
	//x = (float)(0 + (((this.Width / 2) - 31) * Math.Cos(_valueInRadi) * Math.Cos(0 * Math.PI / 180)) - (((this.Width / 2) - 31) * Math.Sin(_valueInRadi) * Math.Sin(0 * Math.PI / 180)));
	//y = (float)(0 + (((this.Height / 2) - 31) * Math.Sin(_valueInRadi) * Math.Cos(0 * Math.PI / 180)) + (((this.Height / 2) - 31) * Math.Cos(_valueInRadi) * Math.Sin(0 * Math.PI / 180)));
	//}

		if (_reverseOrder)
		{
			x = (float)(0 + (((this->width() / 2) - 31) *      cos(0 - (float)_valueInRadi + (180 * M_PI / 180)) *      cos((float)0)) - (((this->width() / 2) - 31) *      sin(0 - (float)_valueInRadi + (180 * M_PI / 180)) *      sin((float)0)));
		  //x = (float)(0 + (((this.Width    / 2) - 31) * Math.Cos(0 - _valueInRadi) * Math.Cos(0)) - (((this.Width    / 2) - 31) * Math.Sin(0 - _valueInRadi) * Math.Sin(0));
			y = (float)(0 + (((this->height() / 2) - 31) *      sin(((float)0) - _valueInRadi + (180 * M_PI / 180)) *      cos((float)0)) + (((this->height() / 2) - 31) *      cos(((float)0) - _valueInRadi + (180 * M_PI / 180)) *      sin((float)0)));
		  //y = (float)(0 + (((this.Height    / 2) - 31) * Math.Sin((0) - _valueInRadi) * Math.Cos(0)) + (((this.Height    / 2) - 31) * Math.Cos((0) - _valueInRadi) * Math.Sin(0)));
		}
		else
		{
			x = (float)(0 + (((this->width() / 2) - 31) * cos(_valueInRadi)) - (((this->width() / 2) - 31) * sin(_valueInRadi) * sin(0 * M_PI / 180)));
			y = (float)(0 + (((this->height() / 2) - 31) * sin(_valueInRadi)) + (((this->height() / 2) - 31) * cos(_valueInRadi) * sin(0 * M_PI / 180)));
		}
		tmpPainter.setPen(needleCenterOutlinePen);
		tmpPainter.setBrush(QBrush(QColor(100,100,100)));
		tmpPainter.drawEllipse((this->width() / 2)-(this->width() / 10),(this->height() / 2) - (this->height() / 10),this->width() / 5,this->height() / 5);

		tmpPainter.setPen(needleOutlinePen);
		tmpPainter.drawLine(this->width()/2,this->height()/2,this->width()/2 + x,this->height()/2 + y);
		tmpPainter.setPen(needlePen);
		tmpPainter.drawLine(this->width()/2,this->height()/2,this->width()/2 + x,this->height()/2 + y);

		tmpPainter.setPen(needleCenterPen);
		tmpPainter.setBrush(QBrush(Qt::SolidPattern));
		tmpPainter.drawEllipse((this->width() / 2)-(this->width() / 16),(this->height() / 2) - (this->height() / 16),this->width() / 8,this->height() / 8);
		//myGraphics.DrawLine(_needleOutlinePen, this.Size.Width / 2, this.Size.Height / 2, (this.Size.Width / 2) + x, (this.Size.Height / 2) + y);

		tmpPainter.end();
	}
	else if (m_style == 2)
	{
		QPainter tmpPainter(this);
		tmpPainter.drawImage(0,0,*_bgImage);
	}
}
void GaugeWidget::setValue(double value)
{
	//_value = value;

	/*_targetValue = value;
	fadeTimer->stop();
	gaugeTimer->start(50);
	*/
	_value = value;
	this->repaint();

	//this->repaint();
}
void GaugeWidget::setColor(QColor outlinecolor, QColor centercolor, QColor topreflectioncolor, QColor bottomreflectioncolor)
{
	Q_UNUSED(outlinecolor);
	Q_UNUSED(centercolor);
	Q_UNUSED(topreflectioncolor);
	Q_UNUSED(bottomreflectioncolor);
}
void GaugeWidget::setColor1(QColor needlecolor, QColor needleoutlinecolor, QColor normaltickcolor, QColor bigtickcolor, QColor warningtickcolor, QColor dangertickcolor)
{
	Q_UNUSED(needlecolor);
	Q_UNUSED(needleoutlinecolor);
	Q_UNUSED(normaltickcolor);
	Q_UNUSED(bigtickcolor);
	Q_UNUSED(warningtickcolor);
	Q_UNUSED(dangertickcolor);
}
void GaugeWidget::setColor2(QColor fontcolor, QColor warningfontcolor, QColor dangerfontcolor,QFont font)
{
	Q_UNUSED(fontcolor);
	Q_UNUSED(warningfontcolor);
	Q_UNUSED(dangerfontcolor);
	Q_UNUSED(font);
}
void GaugeWidget::passEvent(QStringList evt)
{
	QString evts = evt[1];
	setValue(evts.toDouble());
}
void GaugeWidget::startDemo(int max)
{
	demoMax = max;
	demoTimer = new QTimer(this);
	connect(demoTimer,SIGNAL(timeout()),this,SLOT(timerTick()));
	demoTimer->start(500);
}
void GaugeWidget::timerTick()
{
	setValue(rand() % demoMax);
}
void GaugeWidget::fadeTimerTick()
{
	this->repaint();
	fadeCount++;
	if (fadeCount > 50)
	{
		resizeDraw = true;
		fadeCount = 0;
		//fadeTimer->stop();
		//resizeDraw = true;
		//repaint();
	}
}
void GaugeWidget::gaugeTimerTick()
{
	_value = _value + ((_targetValue - _value) * 0.05);
	if (abs(_value - _targetValue) < 10)
	{
		fadeCount = 0;
		_value = _targetValue;
		gaugeTimer->stop();
		fadeTimer->start(50);
	}
	this->repaint();
}
void GaugeWidget::setFade(int fade)
{
	fadeAmount = fade;
	drawBackground();
}
void GaugeWidget::show()
{
	resizeDraw = true;
	//fadeTimer->start(50);
	QWidget::show();
}

void GaugeWidget::setFadingOn(bool fade)
{
	m_fadeEnabled = fade;
}
void GaugeWidget::setGaugeStyle(int style)
{
	m_style = style;
}
