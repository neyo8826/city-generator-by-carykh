#pragma once

#define DISABLE_COPY_SEMANTICS(Class) \
  public: \
  Class(Class const &) = delete; \
  Class & operator=(Class const &) = delete;
