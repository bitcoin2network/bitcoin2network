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

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "CryptoNote.h"

namespace CryptoNote {

namespace TransactionTypes {
  
  enum class InputType : uint8_t { Invalid, Key, Generating };
  enum class OutputType : uint8_t { Invalid, Key };

  struct GlobalOutput {
    Crypto::PublicKey targetKey;
    uint32_t outputIndex;
  };

  typedef std::vector<GlobalOutput> GlobalOutputsContainer;

  struct OutputKeyInfo {
    Crypto::PublicKey transactionPublicKey;
    size_t transactionIndex;
    size_t outputInTransaction;
  };

  struct InputKeyInfo {
    uint64_t amount;
    GlobalOutputsContainer outputs;
    OutputKeyInfo realOutput;
  };
}

//
// ITransactionReader
// 
class ITransactionReader {
public:
  virtual ~ITransactionReader() { }

  virtual Crypto::Hash getTransactionHash() const = 0;
  virtual Crypto::Hash getTransactionPrefixHash() const = 0;
  virtual Crypto::PublicKey getTransactionPublicKey() const = 0;
  virtual bool getTransactionSecretKey(Crypto::SecretKey& key) const = 0;
  virtual uint64_t getUnlockTime() const = 0;

  // extra
  virtual bool getPaymentId(Crypto::Hash& paymentId) const = 0;
  virtual bool getExtraNonce(BinaryArray& nonce) const = 0;
  virtual BinaryArray getExtra() const = 0;

  // inputs
  virtual size_t getInputCount() const = 0;
  virtual uint64_t getInputTotalAmount() const = 0;
  virtual TransactionTypes::InputType getInputType(size_t index) const = 0;
  virtual void getInput(size_t index, KeyInput& input) const = 0;

  // outputs
  virtual size_t getOutputCount() const = 0;
  virtual uint64_t getOutputTotalAmount() const = 0;
  virtual TransactionTypes::OutputType getOutputType(size_t index) const = 0;
  virtual void getOutput(size_t index, KeyOutput& output, uint64_t& amount) const = 0;

  // signatures
  virtual size_t getRequiredSignaturesCount(size_t inputIndex) const = 0;
  virtual bool findOutputsToAccount(const AccountPublicAddress& addr, const Crypto::SecretKey& viewSecretKey, std::vector<uint32_t>& outs, uint64_t& outputAmount) const = 0;

  // various checks
  virtual bool validateInputs() const = 0;
  virtual bool validateOutputs() const = 0;
  virtual bool validateSignatures() const = 0;

  // serialized transaction
  virtual BinaryArray getTransactionData() const = 0;
};

//
// ITransactionWriter
// 
class ITransactionWriter {
public: 

  virtual ~ITransactionWriter() { }

  // transaction parameters
  virtual void setUnlockTime(uint64_t unlockTime) = 0;

  // extra
  virtual void setPaymentId(const Crypto::Hash& paymentId) = 0;
  virtual void setExtraNonce(const BinaryArray& nonce) = 0;
  virtual void appendExtra(const BinaryArray& extraData) = 0;

  // Inputs/Outputs 
  virtual size_t addInput(const KeyInput& input) = 0;
  virtual size_t addInput(const AccountKeys& senderKeys, const TransactionTypes::InputKeyInfo& info, KeyPair& ephKeys) = 0;

  virtual size_t addOutput(uint64_t amount, const AccountPublicAddress& to) = 0;
  virtual size_t addOutput(uint64_t amount, const KeyOutput& out) = 0;

  // transaction info
  virtual void setTransactionSecretKey(const Crypto::SecretKey& key) = 0;

  // signing
  virtual void signInputKey(size_t input, const TransactionTypes::InputKeyInfo& info, const KeyPair& ephKeys) = 0;
};

class ITransaction : 
  public ITransactionReader, 
  public ITransactionWriter {
public:
  virtual ~ITransaction() { }

};

}
