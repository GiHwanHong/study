#pragma once

#include "wimage.h"
#include "wimage_t_traits.h"
#include <QRect>

template<typename T, int C>
class WImageT;

template<typename T, int C>
class WInputImageT
{
	WInputImageT(); // cannot use thi ctor
public:
	typedef const WImageT<T,C> ImageType;
	WInputImageT(const ImageType& _const_image,
				 const QPoint& _topLeft)
		: m_const_image(_const_image)
		, m_topLeft(_topLeft)
	{
	}
	cv::Mat matrix(const QSize& roiSize) const {
		cv::Rect rect(m_topLeft.x(), m_topLeft.y(),
					  roiSize.width(), roiSize.height());
		return ((const cv::Mat&)m_const_image)(rect);
	}
	cv::Mat matrix(const QRect& roi) const {
		cv::Rect rect(roi.x(), roi.y(),
					  roi.width(), roi.height());
		return ((const cv::Mat&)m_const_image)(rect);
	}
	operator const T* () const
	{
		//  NOTE : y=row, x=col
		return m_const_image->ptr<T>(m_topLeft.y(), m_topLeft.x());
	}
	int channels() const
	{
		// return C;
		return m_const_image->channels();
	}
	int step() const
	{
		return m_const_image->step1();
	}
	// dimension 에 대한 check도 canInclude로 된다.(side effect).
	// 2차원인경우에만, rows > 0 , cols > 0 이다.
	bool canInclude(const QRect& roi) const
	{
		const cv::Mat& mat = (const cv::Mat&)m_const_image;
		return (mat.rows > 0)
			&& (mat.cols > 0)
			&& ((roi.x() + roi.width()) < mat.cols)
			&& ((roi.y() + roi.height()) < mat.rows);
	}
	bool canExpandTo(const QSize& roiSize) const
	{
		return canInclude(QRect(m_topLeft, roiSize));
	}
	bool hasSameChannelWith(const WInputImageT<T,C>& i0)
	{
		return m_const_image->channels() == i0.m_const_image->channels();
	}
	bool hasSameChannelWith(const WInputImageT<T,C>& i0, const WInputImageT<T,C>& i1)
	{
		// C ?
		int channel = m_const_image->channels();
		return channel == i0.m_const_image->channels()
			&& channel == i1.m_const_image->channels();
	}
protected:
	const WImageT<T,C>& m_const_image;
	QPoint m_topLeft;
};

template<typename T>
struct WMonoInputImageT
{
	typedef WInputImageT<T,1> Type;
};

template<typename T>
struct WColorInputImageT
{
	typedef WInputImageT<T, 3> Type;
};

template<typename T, int C>
class WOutputImageT : public WInputImageT<T,C>
{
	WOutputImageT(); // cannot use this ctor
public:
	typedef WImageT<T,C> ImageType;
	WOutputImageT(ImageType& _image,
				  const QRect& _roi)
		: WInputImageT<T,C>(_image,
							_roi.topLeft())
		, m_image(_image)
		, m_roi(_roi)
	{
	}
	operator T* ()
	{
		//  NOTE : y=row, x=col
		return m_image->ptr<T>(m_roi.y(),m_roi.x());
	}
	cv::Mat matrix() const
	{
		return WInputImageT<T,C>::matrix(m_roi);
	}
	QSize roiSize() const
	{
		return m_roi.size();
	}
	IppiSize ippRoiSize() const
	{
		IppiSize size = {
			m_roi.width(),
			m_roi.height()
		};
		return size;
	}
	const QRect& roi() const
	{
		return m_roi;
	}
	bool canOperateFrom(const WInputImageT<T,C>& i0) const
	{
		return i0.canExpandTo(m_roi.size());
	}
	bool canOperateFrom(const WInputImageT<T,C>& i0, const WInputImageT<T,C>& i1) const
	{
		QSize size = m_roi.size();
		return i0.canExpandTo(size)
			&& i1.canExpandTo(size);
	}
protected:
	ImageType& m_image;
	QRect m_roi;
};

template<typename T>
struct WMonoOutputImageT
{
	typedef WOutputImageT<T, 1> Type;
};

template<typename T>
struct WColorOutputImageT
{
	typedef WOutputImageT<T, 3> Type;
};


template<typename T,int C>
class WImageT : public WImage
{
public:
	typedef WImageTypeTrait<T> Trait;
    WImageT(const WImage& source)
	{
		if (Trait::openCvMatDepth==source->depth()
			&& source->channels() == C)
		{
			*(WImage*)this = source;
		}
	}
	// TODO CHECKME should be virtual or not?
	// maybe not. see opencv comment on cv::Mat_ class in core.hpp
    ~WImageT()
	{
	}
	operator WInputImageT<T,C>() const
	{
		return WInputImageT<T,C>(*this, QPoint(0,0));
	}
	WInputImageT<T,C> operator () (const QPoint& topLeft) const
	{
		return WInputImageT<T,C>(*this, topLeft);
	}
	operator WOutputImageT<T,C>()
	{
		const cv::Mat& mat = (const cv::Mat&)(*this);
		return WOutputImageT<T,C>(*this, QRect(0,0,mat.cols,mat.cols));
	}
	WOutputImageT<T,C> operator ()(const QRect& roi)
	{
		return WOutputImageT<T,C>(*this, roi);
	}
};

template<typename T>
struct WColorImageT
{
	typedef WImageT<T, 3> Type;
};

template<typename T>
struct WMonoImageT
{
	typedef WImageT<T, 1> Type;
};

