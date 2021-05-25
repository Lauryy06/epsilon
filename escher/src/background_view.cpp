#include <escher/background_view.h>
extern "C" {
#include <assert.h>
}
#include <ion.h>
#include <escher/composed_image.h>
#include <algorithm>

BackgroundView::BackgroundView(const ComposedImage * background) :
  View(),
  m_background(background)
{
}

void BackgroundView::drawRect(KDContext * ctx, KDRect rect) const {

    //We need to find the absolute position of the rectangle 
    //to be drawn to select the right pixels of the image
    
    KDPoint contextToImage = KDPoint(ctx->origin().x()-m_frame.x(), ctx->origin().y()-m_frame.y());
    KDPoint imageToContext = KDPoint(-contextToImage.x(), -contextToImage.y());

    KDRect trueRect =  rect.translatedBy(contextToImage);

    KDColor pixelBuffer [ComposedImage::k_blockHeight * Ion::Display::Width];
    assert(Ion::stackSafe());

    int i = trueRect.y() / ComposedImage::k_blockHeight;
    KDCoordinate remainingHeight = trueRect.height();

    while(remainingHeight > 0 && i <= m_background->numberOfImages()) {
      const Image * image = m_background->getImage(i);

      Ion::decompress(
        image->compressedPixelData(),
        reinterpret_cast<uint8_t *>(pixelBuffer), 
        image->compressedPixelDataSize(),
        image->height() * image->width() * sizeof(KDColor)
      );

      //KDRect rectToRedraw = KDRect(rect.x(),std::max(0,rect.y()+rect.height()-remainingHeight),rect.width(),std::min(image->height(),remainingHeight));

      /*if(trueRect.x() == 0 && trueRect.width() == image->width()){
        ctx->fillRectWithPixels(KDRect(0, (rect.bottom()+1)-remainingHeight, image->width(), image->height()), pixelBuffer, nullptr);
      }
      else {*/
      const int k_blockHeight = ComposedImage::k_blockHeight;
          for (int line = std::max(0, trueRect.y()-(i*k_blockHeight)); 
                line < std::min(k_blockHeight, trueRect.y()+trueRect.height()-(i*k_blockHeight)); 
                line++) {
            ctx->fillRectWithPixels(KDRect(rect.x(), rect.y()+rect.height()-remainingHeight, rect.width(), 1), pixelBuffer+(line*image->width())+trueRect.x(), nullptr);
            remainingHeight --;
          }    
      //}
      i++;
    }
}
