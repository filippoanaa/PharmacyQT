#pragma once
#include "Med.h"
#include "MedRepo.h"
#include <qdebug.h>

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd :public UndoAction {
	Med addedMed;
	RepoInterface& repo;

public:
	UndoAdd(RepoInterface& _repo, const Med& m) :repo{ _repo }, addedMed(m) {};
	void doUndo() override {
		repo.del(addedMed);
	}
};

class UndoDelete : public UndoAction {
	Med deletedMed;
	RepoInterface& repo;

public:
	UndoDelete(RepoInterface& _repo, const Med& m) : repo{ _repo }, deletedMed{ m } {} 

	void doUndo() override {
			repo.store(deletedMed);
	}
};


class UndoUpdate : public UndoAction {
	Med oldMed, newMed;
	RepoInterface& repo;

public:
	UndoUpdate(RepoInterface& _repo, const Med& _oldMed, const Med& _newMed) : repo{ _repo }, oldMed{ _oldMed }, newMed{ _newMed } {};
	void doUndo() override {
		repo.del(newMed);
		repo.store(oldMed);
	}
};
