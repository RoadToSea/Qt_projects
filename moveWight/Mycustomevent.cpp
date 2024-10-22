#include "Mycustomevent.h"

const QEvent::Type MycustomEvent::customType = static_cast<QEvent::Type>(QEvent::registerEventType());
