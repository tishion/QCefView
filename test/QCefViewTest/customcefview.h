#ifndef CUSTOMCEFVIEW_H
#define CUSTOMCEFVIEW_H

#include <include/QCefView.h>

class CustomCefView : public QCefView
{
  Q_OBJECT

public:
  CustomCefView(const QString url, QWidget* parent = 0);
  ~CustomCefView();

  void changeColor();

protected:
  virtual void onConsoleMessage(const QString& message, int level, const QString& source, int line) override;

  virtual void onDraggableRegionChanged(const QRegion& region) override;

  virtual void onQCefUrlRequest(const QString& url) override;

  virtual void onQCefQueryRequest(const QCefQuery& query) override;

  virtual void onInvokeMethodNotify(int browserId,
                                    int frameId,
                                    const QString& method,
                                    const QVariantList& arguments) override;

private:
};

#endif // CUSTOMCEFVIEW_H
