#ifndef ESCHER_BACKGROUND_VIEW_H
#define ESCHER_BACKGROUND_VIEW_H

#include <escher/view.h>
#include <escher/composed_image.h>

class BackgroundView : public View {
public:
  BackgroundView(const ComposedImage * background);
  void drawRect(KDContext * ctx, KDRect rect) const override;
private:
  const ComposedImage * m_background;
};

#endif