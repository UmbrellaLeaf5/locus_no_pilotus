#include <qcustomplot.h>

namespace custom_plot {

/// @brief Class of the arc shape
class ItemArc : public QCPAbstractItem {
 public:
  explicit ItemArc(QCustomPlot *parentPlot);
  virtual ~ItemArc() override;

  QPen Pen() const { return mPen; }
  QPen SelectedPen() const { return mSelectedPen; }
  QBrush Brush() const { return mBrush; }
  QBrush SelectedBrush() const { return mSelectedBrush; }

  void SetPen(const QPen &pen);
  void SetSelectedPen(const QPen &pen);
  void SetBrush(const QBrush &brush);
  void SetSelectedBrush(const QBrush &brush);

  virtual double selectTest(const QPointF &pos, bool onlySelectable,
                            QVariant *details = nullptr) const override;

  QCPItemPosition *const topLeft;
  QCPItemPosition *const bottomRight;
  QCPItemAnchor *const topLeftRim;
  QCPItemAnchor *const top;
  QCPItemAnchor *const topRightRim;
  QCPItemAnchor *const right;
  QCPItemAnchor *const bottomRightRim;
  QCPItemAnchor *const bottom;
  QCPItemAnchor *const bottomLeftRim;
  QCPItemAnchor *const left;
  QCPItemAnchor *const center;

 protected:
  enum AnchorIndex {
    aiTopLeftRim,
    aiTop,
    aiTopRightRim,
    aiRight,
    aiBottomRightRim,
    aiBottom,
    aiBottomLeftRim,
    aiLeft,
    aiCenter
  };

  QPen mPen, mSelectedPen;
  QBrush mBrush, mSelectedBrush;

  virtual void draw(QCPPainter *painter) Q_DECL_OVERRIDE;
  virtual QPointF anchorPixelPosition(int anchorId) const Q_DECL_OVERRIDE;

  QPen MainPen() const;
  QBrush MainBrush() const;
};

/**
 * @brief Creates an arc item and sets default values.
 * @details The created item is automatically registered with \a parentPlot.
 * This QCustomPlot instance takes ownership of the item, so do not delete it
 * manually but use QCustomPlot::removeItem() instead.
 * @param parentPlot
 */
ItemArc::ItemArc(QCustomPlot *parentPlot)
    : QCPAbstractItem(parentPlot),
      topLeft(createPosition(QLatin1String("topLeft"))),
      bottomRight(createPosition(QLatin1String("bottomRight"))),
      topLeftRim(createAnchor(QLatin1String("topLeftRim"), aiTopLeftRim)),
      top(createAnchor(QLatin1String("top"), aiTop)),
      topRightRim(createAnchor(QLatin1String("topRightRim"), aiTopRightRim)),
      right(createAnchor(QLatin1String("right"), aiRight)),
      bottomRightRim(
          createAnchor(QLatin1String("bottomRightRim"), aiBottomRightRim)),
      bottom(createAnchor(QLatin1String("bottom"), aiBottom)),
      bottomLeftRim(
          createAnchor(QLatin1String("bottomLeftRim"), aiBottomLeftRim)),
      left(createAnchor(QLatin1String("left"), aiLeft)),
      center(createAnchor(QLatin1String("center"), aiCenter)) {
  topLeft->setCoords(0, 1);
  bottomRight->setCoords(1, 0);

  SetPen(QPen(Qt::black));
  SetSelectedPen(QPen(Qt::blue, 2));
  SetBrush(Qt::NoBrush);
  SetSelectedBrush(Qt::NoBrush);
}

ItemArc::~ItemArc() {}

/**
 * @brief Sets the pen that will be used to draw the line of the arc
 * @param pen
 * @see setSelectedPen, setBrush
 */
void ItemArc::SetPen(const QPen &pen) { mPen = pen; }

/**
 * @brief Sets the pen that will be used to draw the line of the arc when
 * selected
 * @param pen
 * @see setPen, setSelected
 */
void ItemArc::SetSelectedPen(const QPen &pen) { mSelectedPen = pen; }

/**
 * @brief Sets the brush that will be used to fill the arc.
 * To disable filling, set @a brush to Qt::NoBrush.
 * @param brush
 * @see setSelectedBrush, setPen
 */
void ItemArc::SetBrush(const QBrush &brush) { mBrush = brush; }

/**
 * @brief Sets the brush that will be used to fill the arc when selected.
 * To disable filling, set @a brush to Qt::NoBrush.
 * @param brush
 * @see setBrush
 */
void ItemArc::SetSelectedBrush(const QBrush &brush) { mSelectedBrush = brush; }

/* check documentation from base class */
double ItemArc::selectTest(const QPointF &pos, bool onlySelectable,
                           QVariant *details) const {
  Q_UNUSED(details)
  if (onlySelectable && !mSelectable) return -1;

  QPointF p1 = topLeft->pixelPosition();
  QPointF p2 = bottomRight->pixelPosition();
  QPointF center((p1 + p2) / 2.0);
  double a = qAbs(p1.x() - p2.x()) / 2.0;
  double b = qAbs(p1.y() - p2.y()) / 2.0;
  double x = pos.x() - center.x();
  double y = pos.y() - center.y();

  // distance to border:
  double c = 1.0 / qSqrt(x * x / (a * a) + y * y / (b * b));
  double result = qAbs(c - 1) * qSqrt(x * x + y * y);
  // filled arc, allow click inside to count as hit:
  if (result > mParentPlot->selectionTolerance() * 0.99 &&
      mBrush.style() != Qt::NoBrush && mBrush.color().alpha() != 0) {
    if (x * x / (a * a) + y * y / (b * b) <= 1)
      result = mParentPlot->selectionTolerance() * 0.99;
  }
  return result;
}

/* check documentation from base class */
void ItemArc::draw(QCPPainter *painter) {
  QPointF p1 = topLeft->pixelPosition();
  QPointF p2 = bottomRight->pixelPosition();

  if (p1.toPoint() == p2.toPoint()) return;

  QRectF arcRect = QRectF(p1, p2).normalized();

  const int clipEnlarge = qCeil(MainPen().widthF());

  QRect clip =
      clipRect().adjusted(-clipEnlarge, -clipEnlarge, clipEnlarge, clipEnlarge);

  if (arcRect.intersects(clip)) {
    painter->setPen(MainPen());
    painter->setBrush(MainBrush());
#ifdef __EXCEPTIONS
    try  // drawArc sometimes throws exceptions if arc is too big
    {
#endif
      // TEMP: this is primary version, 100 is invalid constant
      painter->drawArc(arcRect, 100, 100);
#ifdef __EXCEPTIONS
    } catch (...) {
      qDebug() << Q_FUNC_INFO << "Item too large for memory, setting invisible";
      setVisible(false);
    }
#endif
  }
}

/* check documentation from base class */
QPointF ItemArc::anchorPixelPosition(int anchorId) const {
  QRectF rect = QRectF(topLeft->pixelPosition(), bottomRight->pixelPosition());
  switch (anchorId) {
    case aiTopLeftRim:
      return rect.center() + (rect.topLeft() - rect.center()) * 1 / qSqrt(2);
    case aiTop:
      return (rect.topLeft() + rect.topRight()) * 0.5;
    case aiTopRightRim:
      return rect.center() + (rect.topRight() - rect.center()) * 1 / qSqrt(2);
    case aiRight:
      return (rect.topRight() + rect.bottomRight()) * 0.5;
    case aiBottomRightRim:
      return rect.center() +
             (rect.bottomRight() - rect.center()) * 1 / qSqrt(2);
    case aiBottom:
      return (rect.bottomLeft() + rect.bottomRight()) * 0.5;
    case aiBottomLeftRim:
      return rect.center() + (rect.bottomLeft() - rect.center()) * 1 / qSqrt(2);
    case aiLeft:
      return (rect.topLeft() + rect.bottomLeft()) * 0.5;
    case aiCenter:
      return (rect.topLeft() + rect.bottomRight()) * 0.5;
  }

  qDebug() << Q_FUNC_INFO << "invalid anchorId" << anchorId;
  return {};
}

/**
 * @brief Returns the pen that should be used for drawing lines.
 * Returns mPen when the item is not selected and mSelectedPen when it is.
 * @return QPen
 */
QPen ItemArc::MainPen() const { return mSelected ? mSelectedPen : mPen; }

/**
 * @brief Returns the brush that should be used for drawing fills of the item.
 * Returns mBrush when the item is not selected and mSelectedBrush when it is.
 * @return QBrush
 */
QBrush ItemArc::MainBrush() const {
  return mSelected ? mSelectedBrush : mBrush;
}

}  // namespace custom_plot
