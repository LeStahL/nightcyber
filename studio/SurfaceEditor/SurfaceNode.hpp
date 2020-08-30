#ifndef SURFACE_NODE_HPP
#define SURFACE_NODE_HPP

#include <QByteArray>
#include <QList>
#include <QPointF>
#include <QString>
#include <QVariant>

class SurfaceNode
{
public:
  SurfaceNode(QString identifier);
  SurfaceNode(QVariant serial);
  SurfaceNode(QByteArray serialBinary);

  virtual ~SurfaceNode();

  virtual QVariant serialize();
  virtual QByteArray serializeBinary();

  virtual const QString toString() const;

  const SurfaceNode* parent() const;
  void setParent(const SurfaceNode* parent);

  const SurfaceNode* childAt(int index) const;
  void appendChild(const SurfaceNode* child);
  int nChildren() const;

  void setIdentifier(const QString identifier);
  const QString identifier() const;

private:
  QString m_identifier;
  SurfaceNode* m_parent;
  QList<SurfaceNode*> m_children;
};

#endif
