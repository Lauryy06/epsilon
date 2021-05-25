#ifndef ESCHER_COMPOSED_IMAGE_H
#define ESCHER_COMPOSED_IMAGE_H

#include <escher/image.h>

class ComposedImage {
public:
  constexpr ComposedImage(KDCoordinate width, KDCoordinate height, const Image images[], int numberOfImages) :
    m_width(width), m_height(height), m_images(images), m_numberOfImages(numberOfImages) {}
  KDCoordinate width() const { return m_width; }
  KDCoordinate height() const { return m_height; }
  int numberOfImages() const { return m_numberOfImages; }
  const Image * getImage(int i) const { return &m_images[i]; }
  //12 is a number such that the size of the KDColor array can't exceed 
  //4000 after decompression in order not to overload the ram.
  const static int k_blockHeight = 12;
private:
  const KDCoordinate m_width;
  const KDCoordinate m_height;
  const Image *m_images;
  const int m_numberOfImages;
};

#endif
