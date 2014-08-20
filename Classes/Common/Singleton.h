//  单件

#ifndef __SINGLETON_H__
#define __SINGLETON_H__
#include <assert.h>
template <typename T>
class  CSingleton {
protected:
  static    T    *m_pInstance;

public:
  CSingleton(void) {
    assert(!m_pInstance);
    m_pInstance = static_cast<T *>(this);
  }

  ~CSingleton(void) {
    assert(m_pInstance);
    m_pInstance = 0;
  }

  static T &sharedInstance(void) {
    if (m_pInstance == 0) {
      m_pInstance = new T;
    }

    return (*m_pInstance);
  }

  static T *sharedInstancePtr(void) {
    if (m_pInstance == 0) {
      m_pInstance = new T;
    }

    return (m_pInstance);
  }
};

template<typename T>
T *CSingleton<T>::m_pInstance = 0;

#endif