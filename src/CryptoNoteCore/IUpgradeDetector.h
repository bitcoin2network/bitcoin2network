/*
 * Copyright (c) 2018, The bitcoin2network developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of bitcoin2network.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#pragma once
#include <cstdint>
#include <CryptoNoteCore/Currency.h>

namespace CryptoNote {

class IUpgradeDetector {
public:
  enum : uint32_t {
    UNDEF_HEIGHT = static_cast<uint32_t>(-1)
  };

  virtual uint8_t targetVersion() const = 0;
  virtual uint32_t upgradeIndex() const = 0;
  virtual ~IUpgradeDetector() { }
};

std::unique_ptr<IUpgradeDetector> makeUpgradeDetector(uint8_t targetVersion, uint32_t upgradeIndex);

}
